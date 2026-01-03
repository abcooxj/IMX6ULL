#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/string.h>
#include <linux/irq.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <linux/regmap.h>
#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>
#include <linux/iio/buffer.h>
#include <linux/iio/trigger.h>
#include <linux/iio/triggered_buffer.h>
#include <linux/iio/trigger_consumer.h>
#include <linux/unaligned/be_byteshift.h>
#include "icm20608reg.h"

#define ICM20608_CNT   1
#define ICM20608_NAME  "icm20608"
#define ICM20608_TEMP_OFFSET	     0  /*温度的偏移量*/
#define ICM20608_TEMP_SCALE		     326800000 /*温度换算的缩放比例*/

/*
 * icm20608陀螺仪分辨率，对应250、500、1000、2000，计算方法：
 * 以正负250度量程为例，500/2^16=0.007629，扩大1000000倍，就是7629
 */
static const int gyro_scale_icm20608[] = {7629, 15258, 30517, 61035};

/* 
 * icm20608加速度计分辨率，对应2、4、8、16 计算方法：
 * 以正负2g量程为例，4/2^16=0.000061035，扩大1000000000倍，就是61035
 */
static const int accel_scale_icm20608[] = {61035, 122070, 244140, 488281};


/* 
 * ICM20608的扫描元素，3轴加速度计、
 * 3轴陀螺仪、1路温度传感器，1路时间戳 
 */
enum inv_icm20608_scan {
	INV_ICM20608_SCAN_ACCL_X,
	INV_ICM20608_SCAN_ACCL_Y,
	INV_ICM20608_SCAN_ACCL_Z,
	INV_ICM20608_SCAN_TEMP,
	INV_ICM20608_SCAN_GYRO_X,
	INV_ICM20608_SCAN_GYRO_Y,
	INV_ICM20608_SCAN_GYRO_Z,
	INV_ICM20608_SCAN_TIMESTAMP,
};

// info_mask_shared_by_type同一个类型的通道文件共享的量程刻度
//**scan_type                  扫面的数据类型
//* *info_mask_separate 分开独立文件，比如原始值和校准值
// scan_type数据类型
// modified = 1, 必须为1             	.channel2 = _channel2,  通道修饰符
	
//_index索引
// endianness  IIO_BE大端模式
#define ICM20608_CHAN(_type, _channel2, _index)                    \
	{                                                             \
		.type = _type,                                        \
		.modified = 1,                                        \
		.channel2 = _channel2,                                \
        .info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	      \
				      BIT(IIO_CHAN_INFO_CALIBBIAS),   \
		.scan_index = _index,                                 \
		.scan_type = {                                        \
				.sign = 's' ,                       \
				.realbits = 16,                       \
				.storagebits = 16,                    \
				.shift = 0,                           \
				.endianness = IIO_BE,                 \
			     },                                       \
	}

/*icm20608通道*/
/*IIO_CHAN_INFO_RAW：原始值
 *IIO_CHAN_INFO_OFFSET：校准值，偏置，offset的值
 *IIO_CHAN_INFO_SCALE：分辨率
 */
static const struct iio_chan_spec icm20608_channels[] = {
    /*温度*/
    {
        .type = IIO_TEMP,
        .info_mask_separate = BIT(IIO_CHAN_INFO_RAW) 
                            | BIT(IIO_CHAN_INFO_OFFSET) 
                            | BIT(IIO_CHAN_INFO_SCALE),
        .scan_index = INV_ICM20608_SCAN_TEMP,
        .scan_type = {
            .sign = 's',
            .realbits = 16,
            .storagebits = 16,
            .shift = 0,
            .endianness = IIO_BE,
        },
    },
    /* 加速度X，Y，Z三个通道*/
    /*  必须在  iio_chan_type    iio_modifier    自己定义   */
    ICM20608_CHAN(IIO_ACCEL, IIO_MOD_X, INV_ICM20608_SCAN_ACCL_X), /* 加速度X轴 */
    ICM20608_CHAN(IIO_ACCEL, IIO_MOD_Y, INV_ICM20608_SCAN_ACCL_Y), /* 加速度Y轴 */
    ICM20608_CHAN(IIO_ACCEL, IIO_MOD_Z, INV_ICM20608_SCAN_ACCL_Z), /* 加速度Z轴 */

    /* 陀螺仪X，Y，Z三个通道*/
    ICM20608_CHAN(IIO_ANGL_VEL, IIO_MOD_X, INV_ICM20608_SCAN_GYRO_X), /* 陀螺仪X轴 */
    ICM20608_CHAN(IIO_ANGL_VEL, IIO_MOD_Y, INV_ICM20608_SCAN_GYRO_Y), /* 陀螺仪X轴 */
    ICM20608_CHAN(IIO_ANGL_VEL, IIO_MOD_Z, INV_ICM20608_SCAN_GYRO_Z), /* 陀螺仪X轴 */

};

//**设备结构体 */
struct icm20608_dev{
    struct spi_device *spi;
    struct regmap *regmap;
    struct regmap_config regmap_config;
    struct mutex lock;/*互斥结构体，锁*/
};

//!!
/*
 *static struct icm20608_dev icm20608dev;
 *不要的原因是：iio架构是icm20608_dev设备结构体是和iio_dev一起申请的，所以不能单独申请
 */


//**ICM20608读取单个寄存器 */
static unsigned char icm20608_read_onereg(struct icm20608_dev *dev, u8 reg)
{
    u8 ret=0;
    unsigned int data = 0;
    ret=regmap_read(dev->regmap, reg, &data);
    //icm20608_read_regs(dev, reg, &data, 1);
    return (u8)data;
}

//**ICM20608写一个寄存器 */
static void icm20608_write_onereg(struct icm20608_dev *dev, u8 reg, u8 value)
{
    regmap_write(dev->regmap, reg, value);
    //icm20608_write_regs(dev, reg, &buf, 1);
}


//**ICM20608初始化 */
void icm20608_reginit(struct icm20608_dev *dev)
{
    u8 value  = 0;

    icm20608_write_onereg(dev, ICM20_PWR_MGMT_1, 0x80); /* 复位，复位后为0x40,睡眠模式          */  
    mdelay(50);
    icm20608_write_onereg(dev, ICM20_PWR_MGMT_1, 0x01);   /* 关闭睡眠，自动选择时钟                   */
    mdelay(50);
 
    value = icm20608_read_onereg(dev, ICM20_WHO_AM_I);
    printk("ICM20608 ID = %#X\r\n", value);

    value = icm20608_read_onereg(dev, ICM20_PWR_MGMT_1);
    printk("ICM20_PWR_MGMT_1 = %#X\r\n", value);

    icm20608_write_onereg(dev, ICM20_SMPLRT_DIV, 0x00); 	/* 输出速率是内部采样率					*/
	icm20608_write_onereg(dev, ICM20_GYRO_CONFIG, 0x18); 	/* 陀螺仪±2000dps量程 				*/
	icm20608_write_onereg(dev, ICM20_ACCEL_CONFIG, 0x18); 	/* 加速度计±16G量程 					*/
	icm20608_write_onereg(dev, ICM20_CONFIG, 0x04); 		/* 陀螺仪低通滤波BW=20Hz 				*/
	icm20608_write_onereg(dev, ICM20_ACCEL_CONFIG2, 0x04); /* 加速度计低通滤波BW=21.2Hz 			*/
	icm20608_write_onereg(dev, ICM20_PWR_MGMT_2, 0x00); 	/* 打开加速度计和陀螺仪所有轴 				*/
	icm20608_write_onereg(dev, ICM20_LP_MODE_CFG, 0x00); 	/* 关闭低功耗 						*/
	icm20608_write_onereg(dev, ICM20_FIFO_EN, 0x00);		/* 关闭FIFO	 */

}

/*用于设置校准值或其他参数，通过计算偏移后调用 regmap_bulk_write 将数据写入寄存器。*/
static int icm20608_sensor_set(struct icm20608_dev *dev, int reg,int axis, int val)
{
    int ind, result;
    __be16 d = cpu_to_be16(val); // 将 CPU 本机字节序的整数转换为 16 位大端格式，存入变量 d
    ind = (axis - IIO_MOD_X) * 2; // axis是传入的值，IIO_MOD_X是X轴的偏移量，乘以2是因为寄存器是16位宽的
    result = regmap_bulk_write(dev->regmap, reg + ind, (u8 *)&d, 2); // 将 2 个字节的数据写入到寄存器地址 reg + ind
    if (result)
    return -EINVAL;
    
    return 0;
}

/*
* @description  	: 读取ICM20608传感器数据，可以用于陀螺仪、加速度计、温度的读取
* @param - dev	: icm20608设备 
* @param - reg  	: 要读取的通道寄存器首地址。
* @param - anix  	: 需要读取的通道，比如X，Y，Z。
* @param - val  	: 保存读取到的值。
* @return			: 0，成功；其他值，错误
*/
static int icm20608_sensor_show(struct icm20608_dev *dev, int reg,
       int axis, int *val)
{
    int ind, result;
    __be16 d;

    ind = (axis - IIO_MOD_X) * 2; // 得到当前轴对应的寄存器地址偏移值
    result = regmap_bulk_read(dev->regmap, reg + ind, (u8 *)&d, 2);
    if (result)
    return -EINVAL;
    /* 使用 be16_to_cpup(&d) 将 16 位大端格式数据转换为 CPU 可用的格式，并赋值给 *val。
    这里还做了类型转换为 short，因为陀螺仪和加速度计的数据是 16 位的。*/
     *val = (short)be16_to_cpup(&d);

    return IIO_VAL_INT;
}

/*
* @description  		: 读取ICM20608陀螺仪、加速度计、温度通道值
* @param - indio_dev	: iio设备 
* @param - chan  		: 通道。
* @param - val  		: 保存读取到的通道值。
* @return				: 0，成功；其他值，错误
*/
static int icm20608_read_channel_data(struct iio_dev *indio_dev,
         struct iio_chan_spec const *chan,
         int *val)
{
    struct icm20608_dev *dev = iio_priv(indio_dev);//通过私有数据获得icm20608_dev的指针
    int ret = 0;

    switch (chan->type) 
    {
        case IIO_ANGL_VEL:	/* 读取陀螺仪数据 */
        ret = icm20608_sensor_show(dev, ICM20_GYRO_XOUT_H, chan->channel2, val);  /* channel2为X、Y、Z轴 */
        break;
        case IIO_ACCEL:		/* 读取加速度计数据 */
        ret = icm20608_sensor_show(dev, ICM20_ACCEL_XOUT_H, chan->channel2, val); /* channel2为X、Y、Z轴 */
        break;
        case IIO_TEMP:		/* 读取温度 */
        ret = icm20608_sensor_show(dev, ICM20_TEMP_OUT_H, IIO_MOD_X, val);  
        break;
        default:
        ret = -EINVAL;
        break;
    }
    return ret;
}

/*
* @description  	: 设置ICM20608的陀螺仪计量程(分辨率)
* @param - dev	: icm20608设备
* @param - val   	: 量程(分辨率值)。
* @return			: 0，成功；其他值，错误
*/
static int icm20608_write_gyro_scale(struct icm20608_dev *dev, int val)
{
    int result, i;
    u8 d;
    /*遍历 gyro_scale_icm20608 陀螺仪数组，查找哪个下标的值与传入 val 相等
     *ARRAY_SIZE求出数组包含的个数
     */
    for (i = 0; i < ARRAY_SIZE(gyro_scale_icm20608); ++i) 
    {
        if (gyro_scale_icm20608[i] == val) 
        {
        d = (i << 3);
        /*过 regmap_write 将计算后的值写入 ICM20_GYRO_CONFIG 寄存器*/
        result = regmap_write(dev->regmap, ICM20_GYRO_CONFIG, d);
        if (result)
            return result;
        return 0;
        }
    }
    return -EINVAL;
}

/*
* @description  	: 设置ICM20608的加速度计量程(分辨率)
* @param - dev	: icm20608设备
* @param - val   	: 量程(分辨率值)。
* @return			: 0，成功；其他值，错误
*/
static int icm20608_write_accel_scale(struct icm20608_dev *dev, int val)
{
    int result, i;
    u8 d;
    /*遍历 accel_scale_icm20608 加速度数组*/
    for (i = 0; i < ARRAY_SIZE(accel_scale_icm20608); ++i) 
    {
        if (accel_scale_icm20608[i] == val) 
        {
            d = (i << 3);
            result = regmap_write(dev->regmap, ICM20_ACCEL_CONFIG, d);
            if (result)
                return result;
            return 0;
        }
    }
    return -EINVAL;
}

static int icm20608_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	struct icm20608_dev *dev = iio_priv(indio_dev);
	int ret = 0;
	unsigned char regdata = 0;

	switch (mask) 
    {
	case IIO_CHAN_INFO_RAW:								/* 读取ICM20608加速度计、陀螺仪、温度传感器原始值 */
    /*对设备加锁后调用 icm20608_read_channel_data 获取原始数据，解锁后返回结果。*/
		mutex_lock(&dev->lock);								/* 上锁 			*/
		ret = icm20608_read_channel_data(indio_dev, chan, val); 	/* 读取通道值 */
		mutex_unlock(&dev->lock);							/* 释放锁 			*/
		return ret;
    /*通过位操作提取出寄存器中设置的量程索引，然后从预定义数组中获取对应的分辨率数值，
     *返回格式分别为“整数+微小数”或“整数+纳小数”
     */
    case IIO_CHAN_INFO_SCALE:
		switch (chan->type) /*选择通道类型*/
        {
		case IIO_ANGL_VEL:
			mutex_lock(&dev->lock);
            /*调用 icm20608_read_onereg 读取寄存器 ICM20_GYRO_CONFIG 的内容
             *然后右移 3 位，把该位域调整到低位，得到一个索引值 regdata，该索引用于查找预定义的分辨率数组
             */
            regdata = (icm20608_read_onereg(dev, ICM20_GYRO_CONFIG) & 0X18) >> 3;
            /*将返回值的整数部分设置为 0。因为量程的数值都是以小数部分表示的，实际值由 *val2 决定*/
            *val  = 0;
			*val2 = gyro_scale_icm20608[regdata];
			mutex_unlock(&dev->lock);
			return IIO_VAL_INT_PLUS_MICRO;	/* 值为val+val2/1000000 */
		case IIO_ACCEL:
			mutex_lock(&dev->lock);
			regdata = (icm20608_read_onereg(dev, ICM20_ACCEL_CONFIG) & 0X18) >> 3;
			*val = 0;
			*val2 = accel_scale_icm20608[regdata];;
			mutex_unlock(&dev->lock);
            return IIO_VAL_INT_PLUS_NANO; /* 需要除以 10^9 得到实际的小数值值为val+val2/1000000000 */
        case IIO_TEMP:					
			*val = ICM20608_TEMP_SCALE/ 1000000;
			*val2 = ICM20608_TEMP_SCALE % 1000000;
            return IIO_VAL_INT_PLUS_MICRO; /*除以 10^6 得到实际的小数值。 值为val+val2/1000000 */
        default:
			return -EINVAL;
		}
		return ret;
	case IIO_CHAN_INFO_OFFSET:		/* ICM20608温度传感器offset值 */
		switch (chan->type) 
        {
		case IIO_TEMP:
			*val = ICM20608_TEMP_OFFSET;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
		return ret;
	case IIO_CHAN_INFO_CALIBBIAS:	/* ICM20608加速度计和陀螺仪校准值 */
		switch (chan->type) 
        {
		case IIO_ANGL_VEL:		/* 陀螺仪的校准值 */
			mutex_lock(&dev->lock);
			ret = icm20608_sensor_show(dev, ICM20_XG_OFFS_USRH, chan->channel2, val);
			mutex_unlock(&dev->lock);
			return ret;
		case IIO_ACCEL:			/* 加速度计的校准值 */
			mutex_lock(&dev->lock);	
			ret = icm20608_sensor_show(dev, ICM20_XA_OFFSET_H, chan->channel2, val);
			mutex_unlock(&dev->lock);
			return ret;
		default:
			return -EINVAL;
		}
		
	default:
		return ret -EINVAL;
	}
}	

/*
  * @description     	: 写函数，当向sysfs中的文件写数据的时候最终此函数会执行，一般在此函数
  * 					：里面设置传感器，比如量程等。
  * @param - indio_dev	: iio_dev
  * @param - chan   	: 通道
  * @param - val   		: 应用程序写入的值，如果是小数值的话，val是整数部分。
  * @param - val2   	: 应用程序写入的值，如果是小数值的话，val2是小数部分。
  * @return				: 0，成功；其他值，错误
  */
static int icm20608_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct icm20608_dev *dev = iio_priv(indio_dev);
	int ret = 0;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:	/* 设置陀螺仪和加速度计的分辨率 */
		switch (chan->type) {
		case IIO_ANGL_VEL:		/* 设置陀螺仪 */
			mutex_lock(&dev->lock);
			ret = icm20608_write_gyro_scale(dev, val2);
			mutex_unlock(&dev->lock);
			break;
		case IIO_ACCEL:			/* 设置加速度计 */
			mutex_lock(&dev->lock);
			ret = icm20608_write_accel_scale(dev, val2);
			mutex_unlock(&dev->lock);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	case IIO_CHAN_INFO_CALIBBIAS:	/* 设置陀螺仪和加速度计的校准值*/
		switch (chan->type) {
		case IIO_ANGL_VEL:		/* 设置陀螺仪校准值 */
			mutex_lock(&dev->lock);
			ret = icm20608_sensor_set(dev, ICM20_XG_OFFS_USRH,
									    chan->channel2, val);
			mutex_unlock(&dev->lock);
			break;
		case IIO_ACCEL:			/* 加速度计校准值 */
			mutex_lock(&dev->lock);
			ret = icm20608_sensor_set(dev, ICM20_XA_OFFSET_H,
							             chan->channel2, val);
			mutex_unlock(&dev->lock);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}

/*
 * @description     	: 用户空间写数据格式，比如我们在用户空间操作sysfs来设置传感器的分辨率，
 * 					：如果分辨率带小数，那么这个小数传递到内核空间应该扩大多少倍，此函数就是
 *						: 用来设置这个的。
 * @param - indio_dev	: iio_dev
 * @param - chan   	: 通道
 * @param - mask   	: 掩码
 * @return				: 0，成功；其他值，错误
 */
static int icm20608_write_raw_get_fmt(struct iio_dev *indio_dev,
                                      struct iio_chan_spec const *chan, long mask)
{
    switch (mask)
    {
    case IIO_CHAN_INFO_SCALE:
        switch (chan->type)
        {
        case IIO_ANGL_VEL: /* 用户空间写的陀螺仪分辨率数据要乘以1000000 */
            return IIO_VAL_INT_PLUS_MICRO;
        default: /* 用户空间写的加速度计分辨率数据要乘以1000000000 */
            return IIO_VAL_INT_PLUS_NANO;
        }
    default:
        return IIO_VAL_INT_PLUS_MICRO;
    }
    return -EINVAL;
}


/*iio_info*/
static const struct iio_info icm20608_info = {
	.driver_module  = THIS_MODULE,
	.read_raw		= icm20608_read_raw,
	.write_raw		= icm20608_write_raw,
    .write_raw_get_fmt = icm20608_write_raw_get_fmt,
};

static int icm20608_probe(struct spi_device *spi)
{
    int ret=0;
    struct icm20608_dev *dev;
    struct iio_dev *indio_dev;

    printk("icm20608_probe\r\n");

#if 0
//!!使用的是iio架构，所以不需要注册字符设备
    //**搭建字符设备驱动框架，在/dev/ */
   /* 2，注册字符设备 */
   icm20608dev.major = 0;   /* 由系统分配主设备号 */
   if(icm20608dev.major){    /* 给定主设备号 */
       icm20608dev.devid = MKDEV(icm20608dev.major, 0);
       ret = register_chrdev_region(icm20608dev.devid, ICM20608_CNT, ICM20608_NAME);
   } else {                /* 没有给定主设备号 */
       ret = alloc_chrdev_region(&icm20608dev.devid, 0, ICM20608_CNT, ICM20608_NAME);
       icm20608dev.major = MAJOR(icm20608dev.devid);
       icm20608dev.minor = MINOR(icm20608dev.devid);
   }
   if(ret < 0) {
       printk("icm20608 chrdev_region err!\r\n");
       goto fail_devid;
   }
   printk("icm20608 major=%d, minor=%d\r\n", icm20608dev.major, icm20608dev.minor);

   /* 3,注册字符设备 */
   icm20608dev.cdev.owner = THIS_MODULE;
   cdev_init(&icm20608dev.cdev, &icm20608_fops);
   ret = cdev_add(&icm20608dev.cdev, icm20608dev.devid, ICM20608_CNT);
   if(ret < 0) {
       goto fail_cdev;
   }

   /* 4,自动创建设备节点 */
   icm20608dev.class = class_create(THIS_MODULE, ICM20608_NAME);
   if (IS_ERR(icm20608dev.class)) {
       ret = PTR_ERR(icm20608dev.class);
       goto fail_class;
   }

   icm20608dev.device = device_create(icm20608dev.class, NULL,
                icm20608dev.devid, NULL, ICM20608_NAME);
   if (IS_ERR(icm20608dev.device)) {
       ret = PTR_ERR(icm20608dev.device);
       goto fail_device;
   }
#endif

    /*申请iio_dev 和icm20608_dev*/
    indio_dev = devm_iio_device_alloc(&spi->dev,sizeof(*dev));
    if(!indio_dev)
    {
        ret=-ENOMEM;
        goto fail_iio_dev;
    }

    dev=iio_priv(indio_dev);/*得到icm20608_dev首地址*/
    dev->spi=spi;
    spi_set_drvdata(spi,indio_dev);
    mutex_init(&dev->lock);

    /*初始化iio_dev*/
    indio_dev->dev.parent=&spi->dev;
    indio_dev->channels=icm20608_channels;
    indio_dev->num_channels=ARRAY_SIZE(icm20608_channels);
    indio_dev->name=ICM20608_NAME;
    indio_dev->modes=INDIO_DIRECT_MODE;/*直接模式，提供sysfs接口*/
    indio_dev->info=&icm20608_info;

    /*将iio_info注册到内核*/
    ret=iio_device_register(indio_dev);
    if(ret<0)
    {
        dev_err(&spi->dev,"unable to register iio device\r\n");
        goto fail_iio_register;
    }

   /*regmap申请和初始化*/
   dev->regmap_config.reg_bits=8;/*寄存器长度是8bit*/
   dev->regmap_config.val_bits=8;/*寄存器值长度是8bit*/
   dev->regmap_config.read_flag_mask=0x80;/*读标志位是0x80,读掩码*/
   dev->regmap = regmap_init_spi(spi,&dev->regmap_config);
   if(IS_ERR(dev->regmap)) 
    {
    ret = PTR_ERR(dev->regmap);
    goto fail_regmap_init;
    }

   //**初始化spi_device */
   spi->mode = SPI_MODE_0;
    spi_setup(spi);

    //**初始化icm20608 */
    icm20608_reginit(dev);

   return 0;

fail_regmap_init:
   iio_device_unregister(indio_dev);
fail_iio_register:
fail_iio_dev:
   return ret; 
}

static int icm20608_remove(struct spi_device *spi)
{
    int ret=0;
    struct iio_dev *indio_dev = spi_get_drvdata(spi);
    struct icm20608_dev *dev;

    printk("icm20608_remove\r\n");
#if 0
     /* 1,删除字符设备 */
     cdev_del(&icm20608dev.cdev);

     /* 2,注销设备号 */
     unregister_chrdev_region(icm20608dev.devid, ICM20608_CNT);
 
     /* 3,摧毁设备 */
     device_destroy(icm20608dev.class, icm20608dev.devid);
   
     /* 4,摧毁类 */
     class_destroy(icm20608dev.class);

     /* 5、释放片选 */
    gpio_free(icm20608dev.cs_gpio);
#endif

    dev = iio_priv(indio_dev);

    /* 1、注销iio_dev */
    iio_device_unregister(indio_dev);

    /*删除regmap*/
    regmap_exit(dev->regmap);

     return ret;
    
}

//**传统匹配 */
struct spi_device_id icm20608_id[] = {
    {"alientek,icm20608",0},
    {}
};

//**设备树匹配 */
static const struct of_device_id icm20608_of_match[] = {
    { .compatible = "alientek,icm20608"},
    { }
};

//**spi driver */
struct spi_driver icm20608_driver={
    .probe = icm20608_probe,
    .remove = icm20608_remove,
    .driver = {
        .name = "icm20608",
        .owner = THIS_MODULE,
        .of_match_table = icm20608_of_match,
    },
    .id_table = icm20608_id,
};

//**驱动入口函数 */
static int __init icm20608_init(void)
{
    int ret = 0;

   ret=spi_register_driver(&icm20608_driver);

    return ret;
}

//**驱动出口函数 */
static void __exit icm20608_exit(void)
{
    spi_unregister_driver(&icm20608_driver);
}

module_init(icm20608_init);
module_exit(icm20608_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("abcooxj");