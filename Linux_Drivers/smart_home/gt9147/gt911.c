#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/regmap.h>
#include <linux/gpio/consumer.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/input/mt.h>
#include <linux/input/touchscreen.h>
#include <linux/i2c.h>
#include <asm/unaligned.h>

/*abcooxj 学习的文件，GT9147、 GT911 和 GT1151 这三颗触摸芯片几乎一模一样
* 自学，增加多点触摸文件
* 自己理解的代码
* */

#define GT_CTRL_REG 	        0X8040  /* GT9147控制寄存器         */
#define GT_MODSW_REG 	        0X804D  /* GT9147模式切换寄存器        */
#define GT_9xx_CFGS_REG         0X8047  /* GT9147配置起始地址寄存器    */
#define GT_1xx_CFGS_REG         0X8050  /* GT1151配置起始地址寄存器    */
#define GT_CHECK_REG 	        0X80FF  /* GT9147校验和寄存器       */
#define GT_PID_REG 		        0X8140  /* GT9147产品ID寄存器       */

#define GT_GSTID_REG 	        0X814E  /* GT9147当前检测到的触摸情况 */
#define GT_TP1_REG 		        0X814F  /* 第一个触摸点数据地址 */
#define GT_TP2_REG 		        0X8157	/* 第二个触摸点数据地址 */
#define GT_TP3_REG 		        0X815F  /* 第三个触摸点数据地址 */
#define GT_TP4_REG 		        0X8167  /* 第四个触摸点数据地址  */
#define GT_TP5_REG 		        0X816F	/* 第五个触摸点数据地址   */
#define MAX_SUPPORT_POINTS      5       /* 最多5点电容触摸 */

#define GT_REG_DATA_WIDTH             8    /* GT911寄存器的位宽 */
#define BUFFER_SIZE    (GT_REG_DATA_WIDTH * MAX_SUPPORT_POINTS)  /* 读取寄存器时的缓存大小 */


struct gt911_dev {
   struct device_node *node;				/* 设备节点 		       */
   int irq_pin,reset_pin;					/* 中断引脚号,复位引脚		*/
   int irq_num;							/* 中断号 		       */
   int irqtype;							/* 中断类型         */
   void *private_data;						/* 私有数据 	       	   */
   struct i2c_client *client;				/* I2C客户端 		       */
   struct input_dev *input;				/* input结构体 		*/
   int max_x;								/* 最大横坐标   	*/
	int max_y; 								/* 最大纵坐标		*/
};

struct gt911_dev gt911;

const u8 irq_table[] = {IRQ_TYPE_EDGE_RISING, IRQ_TYPE_EDGE_FALLING, IRQ_TYPE_LEVEL_LOW, IRQ_TYPE_LEVEL_HIGH}; /* 中断触发方式 */

/*读取GT911的N个寄存器的值*/
//!!错误原因：原本reg是u8,应改为u16,IIC一次读取写入8字节
static int gt911_read_regs(struct gt911_dev *dev, u16 reg, u8 *buf, int len)
{
   int ret;
   u8 regdata[2];
   struct i2c_msg msg[2];
   struct i2c_client *client = (struct i2c_client *)dev->client;

   /*寄存器是16位，将寄存器拆分成两个数组进行存储*/
   /* GT9147寄存器长度为2个字节 */
   regdata[0] =reg>>8;/*获取高八位的数值*/
   regdata[1] =reg&0xFF;/*获取低八位的数值*/

   /*msg[0]发送要读取的寄存器首地址*/
   msg[0].addr = client->addr;/* ft5x06地址 */
   msg[0].flags = !I2C_M_RD;/*!I2C_M_RD是写操作位的标识符*//* 标记为发送数据 */
   msg[0].buf = &regdata[0];/* 读取的首地址 */
   msg[0].len = 2;/* reg长度*/

   //**msg[1]读数据 */
   msg[1].addr  = client->addr; /* ft5x06地址 */
   msg[1].flags = I2C_M_RD; /*I2C_M_RD是读操作位的标识符*/  /* 标记为读取数据*/  
   msg[1].buf = buf;   /* 读取数据缓冲区 */
   msg[1].len = len;   /* 要读取的数据长度*/           

   //!!return i2c_transfer(client->adapter, msg, 2);

   ret = i2c_transfer(client->adapter, msg, 2);
	if(ret == 2) {
		ret = 0;/*在Linux中，返回值是一个非零数，就是错误数据*/
	} else {
		ret = -EREMOTEIO;
	}
	return ret;
}

/*向GT911写N个寄存器的数据*/
static int gt911_write_regs(struct gt911_dev *dev, u16 reg, u8 *buf, int len)
{
   u8 b[256];//**储存寄存器 */
   struct i2c_msg msg;
   struct i2c_client *client = (struct i2c_client *)dev->client;
   
   /* 构建要发送的数据，也就是寄存器首地址+实际的数据 */
   b[0] = reg>>8;/* 寄存器首地址低8位 */
   b[1] = reg & 0XFF;			/* 寄存器首地址高8位 */
   memcpy(&b[2], buf, len);

   msg.addr  = client->addr; /* 从机地址，也就是GT911地址 ，设置 msg 的 addr 为 I2C 器件地址 */
   msg.flags = 0;           /* 表示为要发送的数据 ，标记为写数据*/
  // printk("addr=%#x\r\n",client->addr);
   msg.buf = b;            /* 要发送的数据，寄存器地址+实际数据 */
   msg.len = len + 2;       /* 要发送的数据长度：寄存器地址长度+实际的数据长度   1是实际长度*/

   return i2c_transfer(client->adapter, &msg, 1);
}

///*gt911中断处理函数*/
//static irqreturn_t gt911_irq_handler(int irq,void *dev_id)
//{
//   int touch_num = 0;/*触摸标志位*/
//   int input_x, input_y;/*触摸点的x坐标，y坐标*/
//   int id = 0;
//   int ret = 0;
//   u8 data;
//   u8 touch_data[5];/*存储数据的数组*/
//   struct gt911_dev *dev = dev_id;
//  
//   ret = gt911_read_regs(dev, GT_GSTID_REG, &data, 1);
//    if (data == 0x00)  {     /* 没有触摸数据，直接返回 */
//        goto fail;
//    } else {                 /* 统计触摸点数据 */
//        touch_num = data & 0x0f;/*将data的低四位数据提取出来，数量信息通常存储在数据的低4位中*/
//    }
//
//    /*单点触摸*/
//    if(touch_num)
//    {
//      gt911_read_regs(dev, GT_TP1_REG, touch_data, 5);/*读取5个触摸点的数据*/
//      id=touch_data[0] & 0x0f;/*提取触摸点的id*//*触摸点的id低4位作为触摸点ID*/
//      if(id==0)
//      {
//         input_x = touch_data[1] | (touch_data[2] << 8);/*提取触摸点的x坐标*/
//         input_y = touch_data[3] | (touch_data[4] << 8);/*提取触摸点的y坐标*/
//
//         input_mt_slot(dev->input,id);/*上报触摸点*/
//         input_mt_report_slot_state(dev->input, MT_TOOL_FINGER, true);/*设置触摸点状态为按下*/
//         input_report_abs(dev->input, ABS_MT_POSITION_X, input_x);/*上报触摸点的x坐标*/
//		   input_report_abs(dev->input, ABS_MT_POSITION_Y, input_y);/*上报触摸点的y坐标*/
//      }
//      else if(touch_num==0)
//      {
//        input_mt_slot(dev->input, id);
//        input_mt_report_slot_state(dev->input, MT_TOOL_FINGER, false);/*设置触摸点状态为抬起*/
//      }
//    }
//
//    //??作用
//    /*如果追踪到的触摸点数量多于当前上报的数量，驱动程序使用 BTN_TOOL_TAP 事件来通知用户空间当前追踪到的触摸点总数量，
//    然后调用 input_mt_report_pointer_emulation 函数将use_count 参数设置为 false。否则的话将 use_count
//     参数设置为 true，表示当前的触摸点数量(此函数会获取到具体的触摸点数量，*/
//	input_mt_report_pointer_emulation(dev->input, true);
//   input_sync(dev->input);/*向输入子系统报告触摸屏的指针模拟状态，并同步输入设备的状态*/
//
//   data=0x00;
//   gt911_write_regs(dev, GT_GSTID_REG, &data, 1);
//
//fail:
//   return IRQ_HANDLED;
//
//}



static irqreturn_t gt911_irq_handler(int irq, void *dev_id)
{
    int touch_num = 0;/*触摸点的数量*/
    int input_x, input_y;/*触摸点的x坐标，y坐标*/
    int id = 0;
    int ret = 0;/*储存函数的返回值*/
    u8 data;/*读取寄存器的数据*/
    u8 touch_data[BUFFER_SIZE];
    u16 touch_index = 0;//!!
    int pos = 0;/*遍历touch_data数组*/
    int report_num = 0;/*统计上报触摸点的数量*/
    int i;
    static u16 last_index = 0;/*储存上一次触摸点的状态,判断是否释放*/
    struct gt911_dev *dev = dev_id;

    ret = gt911_read_regs(dev, GT_GSTID_REG, &data, 1);
    if (data == 0x00)  {     // 没有触摸数据，直接返回
        goto fail;
    } else {                 //统计触摸点数据 
        touch_num = data & 0x0f;/*只取低四位的数据*/
    }

    if(touch_num) //有触摸按下
    {         
        //读取具体的触摸寄存器
        /*如果有数据，就将GT_TP1_REG 读取详细的触摸点数据到 touch_data 数组*/
        gt911_read_regs(dev, GT_TP1_REG, touch_data, BUFFER_SIZE);
        id = touch_data[0]& 0x0f;/*读取第一个触摸点，在touch_data,放到id中*/ //!!

        /*使用位操作设置位掩码，标记已经检测的触摸点
        *0x01为0000 0001，左移id位，表示第id位为1，其他位为0
        *如果 id 为 2，那么 (0x01 << 2) 的二进制结果就是 00000100
        *如果 touch_index 原本为 00000010，而 (0x01 << id) 为 00000100，则进行按位或后的结果为 00000110
        *用来记录多个有效的触摸点
        */
        touch_index |= (0x01<<id);/*检查哪些触摸点是有效的*/
        for(i = 0;i < 5; i++)
        {
            if(touch_index |= (0x01 << i))//!!不能将touch_index &= (0x01 << i)，这样会使画笔连续画，释放不好用
            {
                /*提取X和Y的值，转化为16位整数值
                *touch_data[pos + 1]：存储 X 坐标的低 8 位。
                *touch_data[pos + 2]：存储 X 坐标的高 8 位。
                *touch_data[pos + 3]：存储 Y 坐标的低 8 位。
                *touch_data[pos + 4]：存储 Y 坐标的高 8 位。
                *按位或操作 |：将低字节和高字节合并成一个 16 位的整数。
                */
                input_x  = touch_data[pos + 1] | (touch_data[pos + 2] << 8);
                input_y  = touch_data[pos + 3] | (touch_data[pos + 4] << 8);

                input_mt_slot(dev->input, id); //产生ABS_MT_SLOT 事件 报告是哪个触摸点的坐标 
		        input_mt_report_slot_state(dev->input, MT_TOOL_FINGER, true); // 指定手指触摸  连续触摸
		        input_report_abs(dev->input, ABS_MT_POSITION_X, input_x);  // 上报触摸点坐标信息 
		        input_report_abs(dev->input, ABS_MT_POSITION_Y, input_y);  // 上报触摸点坐标信息

                report_num++;/*统计触摸点的上报数量*/
                if(report_num < touch_num)/*检查是否有未处理的触摸点*/
                {
                    pos += 8;/*每个触摸点在touch_data占用8个字节，将数组指针移动到下一个触摸点数据的起始位置*/
                    id = touch_data[pos];/*在下一个触摸点数据中读取数模点的id*/
                    /*左移 0x01 生成一个仅在对应 id 位置为 1 的位掩码，然后用按位或操作将这个标志加入到 touch_index*/
                    touch_index |= (0x01<<id);
                }
            }
            else{
                input_mt_slot(dev->input, i);/*当前i位没有被上报，指定当前的触摸位置*/
                input_mt_report_slot_state(dev->input, MT_TOOL_FINGER, false);   // 关闭手指触摸 
            }
        }
    } 
    else if(last_index)// 触摸释放
    {                
        for(i = 0;i < 5; i++)
        {
            if(last_index & (0x01 << i))
            {
                input_mt_slot(dev->input, i);
                input_mt_report_slot_state(dev->input, MT_TOOL_FINGER, false);
            }
        }
    }
    /*同步事件*/
    last_index = touch_index;
	input_mt_report_pointer_emulation(dev->input, true);
    input_sync(dev->input);

    /*清理中断*/
    data = 0x00;                //向0X814E寄存器写0
    gt911_write_regs(dev, GT_GSTID_REG, &data, 1);

fail:
	return IRQ_HANDLED;
}

/*复位GT911*/
static int gt911_ts_reset(struct i2c_client *client,struct gt911_dev *dev)
{
   int ret = 0;

   /*申请复位IO*/
   if(gpio_is_valid(dev->reset_pin))/*检查IO是否有效*/
   {
       /*申请复位IO，并且默认输出高电平*/
       ret=devm_gpio_request_one(&client->dev,dev->reset_pin,GPIOF_OUT_INIT_HIGH,"gt9147 reset");
       if(ret)
       {
           printk("request reset gpio failed\n");
           return ret;
       }
   }

   /*1.申请中断IO*/
   //??申请中断这步只能放在这里，不能放在GT911中断，放在GT911中断不能触发中断
   if(gpio_is_valid(dev->irq_pin))
   {
       /*申请中断IO，并且默认输出高电平*/
       ret=devm_gpio_request_one(&client->dev,dev->irq_pin,GPIOF_OUT_INIT_HIGH,"gt9147 int");
       if(ret)
       {
           printk("request irq gpio failed\n");
           return ret;
       }
   }
   

   /*初始化GT911,按照GT9147的时序图要求*/
   gpio_set_value(dev->reset_pin,0);/*拉低复位IO,复位GT911*/

   msleep(10);
   gpio_set_value(dev->reset_pin,1);/*拉高复位IO,释放GT911,    停止复位*/
   msleep(10);
   //$$与设备树的有效电平为低电平有关，与不看时序图的高电平
   gpio_set_value(dev->irq_pin,0);//!!低中断IO,释放GT911, 拉低INT引脚*/
   msleep(50);
   gpio_direction_input(dev->irq_pin);/*INT引脚设置为输入*/

   return 0;

}

/*GT911中断*/
static int gt911_ts_irq(struct i2c_client *client,struct gt911_dev *dev)
{
   int ret = 0;

   /*2.申请中断，client->irq就是IO中断*/
   ret = devm_request_threaded_irq(&client->dev,client->irq,NULL,gt911_irq_handler,
                                 irq_table[dev->irqtype] |IRQF_ONESHOT,client->name,&gt911);/*中断线程化*///!!
   if(ret)
   {
       dev_err(&client->dev, "Unable to request touchscreen IRQ.\n");/*错误信息打印*/
       return ret;
   }
   return 0;
}

/*
 * @description     : GT9147读取固件
 * @param - client 	: 要操作的i2c
 * @param - multidev: 自定义的multitouch设备
 * @return          : 0，成功;其他负值,失败
 */
static int gt911_read_firmware(struct i2c_client *client, struct gt911_dev *dev)
{
	int ret = 0, version = 0;
	u16 id = 0;
	u8 data[7]={0};
	char id_str[5];
	ret = gt911_read_regs(dev, GT_PID_REG, data, 6);/*读取固件ID*/
	if (ret) {
		dev_err(&client->dev, "Unable to read PID.\n");
		return ret;
	}
	memcpy(id_str, data, 4);
	id_str[4] = 0;
    if (kstrtou16(id_str, 10, &id))
        id = 0x1001;
	version = get_unaligned_le16(&data[4]);
	dev_info(&client->dev, "ID %d, version: %04x\n", id, version);
	switch (id) {    /* 由于不同的芯片配置寄存器地址不一样需要判断一下  */
    case 1151:
    case 1158:
    case 5663:
    case 5688:    /* 读取固件里面的配置信息  */
        ret = gt911_read_regs(dev, GT_1xx_CFGS_REG, data, 7);  
		break;
    default:
        ret = gt911_read_regs(dev, GT_9xx_CFGS_REG, data, 7);
		break;
    }
	if (ret) {
		dev_err(&client->dev, "Unable to read Firmware.\n");
		return ret;
	}
	dev->max_x = (data[2] << 8) + data[1];
	dev->max_y = (data[4] << 8) + data[3];
	dev->irqtype = data[6] & 0x3;
	printk("X_MAX: %d, Y_MAX: %d, TRIGGER: 0x%02x", dev->max_x, dev->max_y, dev->irqtype);

	return 0;
}


int gt911_probe(struct i2c_client *client, const struct i2c_device_id *id )
{
   u8 data,ret = 0;
   gt911.client = client;

   /*获取irq和reset引脚*/
   gt911.irq_pin=of_get_named_gpio(client->dev.of_node,"interrupt-gpios", 0);
   gt911.reset_pin=of_get_named_gpio(client->dev.of_node,"reset-gpios", 0);

   /* 2，复位GT9147 */
   ret = gt911_ts_reset(client, &gt911);
   if(ret < 0) {
       goto fail;
   }

   /*3.初始化GT911*/
   data=0x02;
   gt911_write_regs(&gt911,GT_CTRL_REG,&data,1);/*软复位*/
   msleep(100);
   data=0x0;
   gt911_write_regs(&gt911,GT_CTRL_REG,&data,1);/*退出软复位*/
   msleep(100);

  /* 4,初始化GT9147，读取固件  */
	ret = gt911_read_firmware(client, &gt911);
	if(ret != 0) {
		printk("Fail !!! check !!\r\n");
		goto fail;
    }

   /* 5，input设备驱动注册*/
   gt911.input = devm_input_allocate_device(&client->dev);
	if (!gt911.input) {
		ret = -ENOMEM;
		goto fail;
	}
   gt911.input->name = client->name;/*名字*/
   gt911.input->id.bustype = BUS_I2C;/*总线*/
   gt911.input->dev.parent = &client->dev;/*次设备*/

   __set_bit(EV_KEY, gt911.input->evbit);
	__set_bit(EV_ABS, gt911.input->evbit);
	__set_bit(BTN_TOUCH, gt911.input->keybit);

	input_set_abs_params(gt911.input, ABS_X, 0, gt911.max_x, 0, 0);
	input_set_abs_params(gt911.input, ABS_Y, 0, gt911.max_y, 0, 0);
	input_set_abs_params(gt911.input, ABS_MT_POSITION_X,0, gt911.max_x, 0, 0);
	input_set_abs_params(gt911.input, ABS_MT_POSITION_Y,0, gt911.max_y, 0, 0);	     
	ret = input_mt_init_slots(gt911.input, MAX_SUPPORT_POINTS, 0);
	if (ret) {
		goto fail;
	}

	ret = input_register_device(gt911.input);
	if (ret)
		goto fail;
  
   /* 6，最后初始化中断 */
   ret = gt911_ts_irq(client, &gt911);
   if(ret < 0) {
       goto fail;
   }
   return 0;

fail:
   return ret;
}

int gt911_remove(struct i2c_client *client)
{
   input_unregister_device(gt911.input);
   printk("gt911_remove\r\n");
   return 0;
}

/*传统驱动匹配表*/
const struct i2c_device_id gt911_id_table[] ={
   { "goodix,gt9147", 0, },
   { /* sentinel */ }
};

/*设备树匹配表*/
const struct of_device_id gt911_of_match_table[] ={
   {.compatible = "goodix,gt9147" },
   { /* sentinel */ }
};

struct i2c_driver gt911_i2c_driver = {
   .probe=gt911_probe,
   .remove=gt911_remove,
   .driver={
       .name="gt9147",
       .owner=THIS_MODULE,
       .of_match_table=gt911_of_match_table,
   },
   .id_table=gt911_id_table,
};

/*注册I2C驱动函数，不能和gt911_init和gt911_exit出现，重复注册函数*/
//module_i2c_driver(gt911_i2c_driver);

/* 驱动入口函数 */
static int __init gt911_init(void)
{
   int ret=0;
   ret=i2c_add_driver(&gt911_i2c_driver);
   if(ret){
       printk("add gt911 driver failed\n");
   }
   return ret;

}

/* 驱动出口函数 */
static void __exit gt911_exit(void)
{ 
   i2c_del_driver(&gt911_i2c_driver);
}
module_init(gt911_init);
module_exit(gt911_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abcooxj");