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

#define KEYINPUT_CNT          1
#define KEYINPUT_NAME    "keyinput"

#define KEY_NUM            1
#define KEY0VALUE          0X01
#define INVAKEY            0XFF

/* key结构体 */
struct irq_keydesc{
    int gpio;               /* io编号 */
    int irqnum;             /* 中断号 */
    unsigned char value;    /* 键值 */
    char name[10];          /* 名字 */
    irqreturn_t (*handler) (int, void *);  /* 中断处理函数 */
};


/* keyinput设备结构体 */
struct keyinput_dev{
    struct device_node *nd;

    struct irq_keydesc irqkey[KEY_NUM];
    struct timer_list timer; 

    struct input_dev *inputdev;//**输入设备 */
};

struct keyinput_dev keyinputdev; /* irq设备 */

//* 按键中断处理函数 */
static irqreturn_t key0_handler(int irq, void *dev_id)
{
   // int value = 0;
    struct keyinput_dev *dev = dev_id;

#if 0
    value = gpio_get_value(dev->irqkey[0].gpio);
    if(value == 0)//**按下 */
    {
        printk("key0 push!\r\n");
    }
    else if(value == 1)//**松开 */
    {
        printk("key0 release!\r\n");
    }
#endif

    dev->timer.data = (volatile long)dev_id;
    mod_timer(&dev->timer, jiffies + msecs_to_jiffies(20)); /* 20ms定时 */

	return IRQ_HANDLED;
}

/* 定时器处理函数 */
static void timer_func(unsigned long arg) 
{
    int value = 0;
    struct keyinput_dev *dev = (struct keyinput_dev*)arg;

    //printk("timer_func!\r\n");
    value = gpio_get_value(dev->irqkey[0].gpio);//**获取GPIO电平 */
    if(value == 0)   {          /* 按下 */
        //**上报事件按键值 */
        input_event(dev->inputdev, EV_KEY, KEY_0, 1);
        //input_report_key(dev->inputdev, KEY_0, 1);
        input_sync(dev->inputdev);
    } else if(value == 1) {     /* 释放 */
        //**上报事件按键值 */
        input_event(dev->inputdev, EV_KEY, KEY_0, 0);
        input_sync(dev->inputdev);

    }
}


//**按键初始化 */
static int keyio_init(struct keyinput_dev *dev)
{
    int ret = 0;
    int i = 0;
    //**1.按键初始化 */
    dev->nd = of_find_node_by_path("/key");
    if(dev->nd == NULL) 
    {
        ret=-EINVAL;
        goto fail_nd;
    }

    for(i=0;i<KEY_NUM;i++)
    {
        dev->irqkey[i].gpio = of_get_named_gpio(dev->nd, "key-gpios", i);
    }

    for(i=0;i<KEY_NUM;i++)
    {
        memset(dev->irqkey[i].name, 0, sizeof(dev->irqkey[i].name));
        sprintf(dev->irqkey[i].name, "KEY%d", i);
        gpio_request(dev->irqkey[i].gpio, dev->irqkey[i].name);
        gpio_direction_input(dev->irqkey[i].gpio);

        dev->irqkey[i].irqnum=gpio_to_irq(dev->irqkey[i].gpio);//**获取中断号 */
    #if 0
        dev->irqkey[i].irqnum=irq_of_parse_and_map(dev->nd, i);//**获取中断号 */
    #endif
    }

    dev->irqkey[0].handler = key0_handler;
    dev->irqkey[0].value  = KEY_0;

    //**2.按键中断初始化 */
    for(i=0;i<KEY_NUM;i++)
    {
        ret = request_irq(dev->irqkey[i].irqnum, dev->irqkey[i].handler, 
                            IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING, 
                            dev->irqkey[i].name, &keyinputdev);
        if(ret) 
        {
            printk("irq %d request failed!\r\n", dev->irqkey[i].irqnum);
            goto fail_irq;
        }
    }

    /* 3、初始化定时器 */
    init_timer(&keyinputdev.timer);
    keyinputdev.timer.function = timer_func;
    return 0;

    return 0;

fail_irq:
    for(i = 0; i < KEY_NUM; i++) {
        gpio_free(dev->irqkey[i].gpio);
    }
fail_nd:
    return ret;
}

//**入口函数 */
static int __init keyinput_init(void)
{
    int ret = 0;

    //**初始化IO */
    ret=keyio_init(&keyinputdev);
    if(ret<0)
    {
        goto fail_keyinit;
    }

    //**注册input_dev */
    keyinputdev.inputdev = input_allocate_device();
    if(keyinputdev.inputdev==NULL)
    {
        ret=-EINVAL;
        goto fail_keyinit;
    }
    keyinputdev.inputdev->name = KEYINPUT_NAME;
    __set_bit(EV_KEY, keyinputdev.inputdev->evbit);//**按键事件 */
    __set_bit(EV_REP, keyinputdev.inputdev->evbit);//**重复事件 */
    __set_bit(KEY_0, keyinputdev.inputdev->keybit);//**按键值事件 */

    ret=input_register_device(keyinputdev.inputdev);
    if(ret)
    {
        goto fail_input_register;
    }

    return 0;

fail_input_register:
    input_free_device(keyinputdev.inputdev);
fail_keyinit:

    return ret;
}

//**出口函数 */
static void __exit keyinput_exit(void)
{
    int i=0;
    //**释放中断 */
    for(i=0;i<KEY_NUM;i++)
    {
        free_irq(keyinputdev.irqkey[i].irqnum, &keyinputdev);
    }

    //**释放IO */
    for(i=0;i<KEY_NUM;i++)
    {
        gpio_free(keyinputdev.irqkey[i].gpio);
    }

    //**删除定时器 */
    del_timer_sync(&keyinputdev.timer);

    //**注销input_dev */
    input_unregister_device(keyinputdev.inputdev);
    input_free_device(keyinputdev.inputdev);
}

module_init(keyinput_init);
module_exit(keyinput_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abcooxj");