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
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/of_gpio.h>
#include <linux/string.h>
#include <linux/irq.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include "ap3216creg.h"

#define AP3216C_CNT   1
#define AP3216C_NAME  "ap3216c"

struct ap3216c_dev{
    int major;
    int minor;
    dev_t devid;
    struct cdev cdev;
    struct class *class;
    struct device *device;
    void *private_data;
    unsigned short ir,als,ps;
};

static struct ap3216c_dev ap3216cdev;

//**读取AP3216C的N个寄存器 */
static int ap3216c_read_regs(struct ap3216c_dev *dev, u8 reg, void *val, int len)
{
    struct i2c_msg msg[2];//** 类似是i2c传输数据的缓冲区，保存数据的数组，由调用，先发送读取的寄存器的数据，再读取数据*/
                            //**两个msg，一个用于发送寄存器地址，一个用于读取寄存器值 */
    struct i2c_client *client = (struct i2c_client*)dev->private_data;

   //**msg[0]发送要读取的寄存器首地址 */
    msg[0].addr = client->addr;         //**从机地址，也是AP3216C的地址，*/
    msg[0].flags = 0;                   //**要发送的数据 */
    msg[0].buf=&reg;                    //**要发送数据，也就是寄存器地址 */
    msg[0].len = 1;                     //**要发送数据的长度 */

    //**msg[1]读数据 */
    msg[1].addr  = client->addr; /* 从机地址，也就是AP3216C地址*/
    msg[1].flags = I2C_M_RD;     /* 表示读数据 */
    msg[1].buf = val;           /* 接收到的从机发送的数据 */
    msg[1].len = len;             /* 要读取的寄存器长度 */

    return i2c_transfer(client->adapter, msg, 2);
}

//**向AP3216C写N个寄存器的数据 */
static int ap3216c_write_regs(struct ap3216c_dev *dev, u8 reg, u8 *buf, int len)
{
    u8 b[256];//**储存寄存器 */
    struct i2c_msg msg;
    struct i2c_client *client = (struct i2c_client*)dev->private_data;
    
    /* 构建要发送的数据，也就是寄存器首地址+实际的数据 */
    b[0] = reg;//** 寄存器地址 reg 存储在 b 数组的第一个元素中*/
    memcpy(&b[1], buf, len);

    msg.addr  = client->addr; /* 从机地址，也就是AP3216C地址 ，设置 msg 的 addr 为 I2C 器件地址 */
    msg.flags = 0;           /* 表示为要发送的数据 ，标记为写数据*/
    msg.buf = b;            /* 要发送的数据，寄存器地址+实际数据 */
    msg.len = len + 1;       /* 要发送的数据长度：寄存器地址长度+实际的数据长度   1是实际长度*/

	return i2c_transfer(client->adapter, &msg, 1);
}

//**读取AP3216C一个寄存器 */
static u8 ap3216c_read_reg(struct ap3216c_dev *dev,u8 reg)
{
    u8 data=0;
    ap3216c_read_regs(dev,reg,&data,1);

    //return i2c_smbus_read_byte_data(dev->private_data, reg);

    return data;
}

//**向AP3216C一个寄存器写数据 */
static void ap3216c_write_reg(struct ap3216c_dev *dev,u8 reg,u8 data)
{
    u8 buf=0;
    buf=data;
    ap3216c_write_regs(dev, reg, &buf, 1);

}

/* AP3216C数据读取 */
void ap3216c_readdata(struct ap3216c_dev *dev)
{
    unsigned char buf[6];
    unsigned char i = 0;

    /* 循环的读取数据 */
    for(i = 0; i < 6; i++) {
        buf[i] = ap3216c_read_reg(dev, AP3216C_IRDATALOW + i);
    }

    if(buf[0] & 0x80) { /* 为真表示IR和PS数据无效 */
        dev->ir = 0;
        dev->ps = 0;
    } else {
        dev->ir = ((unsigned short)buf[1] << 2) | (buf[0] & 0x03);
        dev->ps = (((unsigned short)buf[5] & 0x3F) << 4) | (buf[4] & 0x0F);
    }

    dev->als  = ((unsigned short)buf[3] << 8) | buf[2];

   // printk("ir = %d, als = %d, ps = %d\r\n", dev->ir, dev->als, dev->ps); 
}

static int ap3216c_open(struct inode *inode, struct file *filp)
{
    unsigned char value = 0;
    filp->private_data = &ap3216cdev;
    printk("ap3216c open\r\n");

    //**初始化AP3216C */
    ap3216c_write_reg(&ap3216cdev,AP3216C_SYSTEMCONG,0X4);
    mdelay(50);
    ap3216c_write_reg(&ap3216cdev,AP3216C_SYSTEMCONG,0X3);

    value=ap3216c_read_reg(&ap3216cdev,AP3216C_SYSTEMCONG);
    printk("ap3216c_systemcong:%#x\r\n",value);
    return 0;
}


ssize_t ap3216c_read(struct file *filp, char __user *buf, size_t cnt, loff_t *off)
{
    long err = 0;
    short data[3];

    struct ap3216c_dev *dev = (struct ap3216c_dev *)filp->private_data;

    /* 向应用返回AP3216C的原始数据 */
    ap3216c_readdata(dev);

    data[0] = dev->ir;
    data[1] = dev->als;
    data[2] = dev->ps;

    err = copy_to_user(buf, data, sizeof(data));

    printk("ap3216c_read\r\n");

    return 0;
}

static int ap3216c_release(struct inode *inode, struct file *filp)
{
    //struct ap3216c_dev *dev = (struct ap3216c_dev*)filp->private_data;
   
    printk("ap3216c_release\r\n");
    return 0;
}



static const struct file_operations ap3216c_fops={
    .owner = THIS_MODULE,
	.open	= ap3216c_open,
    .read   = ap3216c_read,
	.release= ap3216c_release,
};

static int ap3216c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret = 0;

    printk("ap3216c_probe\r\n");
    

    //**搭建字符设备驱动框架，在/dev/ */
    /* 2，注册字符设备 */
    ap3216cdev.major = 0;   /* 由系统分配主设备号 */
    if(ap3216cdev.major){    /* 给定主设备号 */
        ap3216cdev.devid = MKDEV(ap3216cdev.major, 0);
        ret = register_chrdev_region(ap3216cdev.devid, AP3216C_CNT, AP3216C_NAME);
    } else {                /* 没有给定主设备号 */
        ret = alloc_chrdev_region(&ap3216cdev.devid, 0, AP3216C_CNT, AP3216C_NAME);
        ap3216cdev.major = MAJOR(ap3216cdev.devid);
        ap3216cdev.minor = MINOR(ap3216cdev.devid);
    }
    if(ret < 0) {
        printk("ap3216c chrdev_region err!\r\n");
        goto fail_devid;
    }
    printk("ap3216c major=%d, minor=%d\r\n", ap3216cdev.major, ap3216cdev.minor);

    /* 3,注册字符设备 */
    ap3216cdev.cdev.owner = THIS_MODULE;
    cdev_init(&ap3216cdev.cdev, &ap3216c_fops);
    ret = cdev_add(&ap3216cdev.cdev, ap3216cdev.devid, AP3216C_CNT);
    if(ret < 0) {
        goto fail_cdev;
    }

    /* 4,自动创建设备节点 */
    ap3216cdev.class = class_create(THIS_MODULE, AP3216C_NAME);
	if (IS_ERR(ap3216cdev.class)) {
        ret = PTR_ERR(ap3216cdev.class);
		goto fail_class;
    }

    ap3216cdev.device = device_create(ap3216cdev.class, NULL,
			     ap3216cdev.devid, NULL, AP3216C_NAME);
	if (IS_ERR(ap3216cdev.device)) {
        ret = PTR_ERR(ap3216cdev.device);
        goto fail_device;
    }
		
    ap3216cdev.private_data = client;   


    return 0;

fail_device:
    class_destroy(ap3216cdev.class);
fail_class:
    cdev_del(&ap3216cdev.cdev);
fail_cdev:
    unregister_chrdev_region(ap3216cdev.devid, AP3216C_CNT);
fail_devid:
	return ret; 


    return 0;
}

static int ap3216c_remove(struct i2c_client *client)
{
    /* 1,删除字符设备 */
    cdev_del(&ap3216cdev.cdev);

    /* 2,注销设备号 */
    unregister_chrdev_region(ap3216cdev.devid, AP3216C_CNT);

    /* 3,摧毁设备 */
    device_destroy(ap3216cdev.class, ap3216cdev.devid);
  
    /* 4,摧毁类 */
    class_destroy(ap3216cdev.class);
    return 0;
    //return 0;
}

//**传统的匹配表 */
static struct i2c_device_id ap3216c_id[] = {
    {"alientek,ap3216c", 0},
    {}
};

//**设备树匹配表 */
static struct of_device_id ap3216c_of_match[] = {
    { .compatible = "alientek,ap3216c", },
    {}
};

//**i2c_driver */
static struct i2c_driver ap3216c_driver = {
    .probe = ap3216c_probe,
    .remove = ap3216c_remove,
    .driver = {
        .name = "ap3216c",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(ap3216c_of_match),
    },
    .id_table = ap3216c_id,
};

//**驱动入口函数 */
static int __init ap3216c_init(void)
{
    int ret = 0;

    ret=i2c_add_driver(&ap3216c_driver);

    return ret;
}

//**驱动出口函数 */
static void __exit ap3216c_exit(void)
{
    i2c_del_driver(&ap3216c_driver);
}

module_init(ap3216c_init);
module_exit(ap3216c_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abcooxj");