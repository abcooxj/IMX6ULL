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
#include <linux/poll.h>
#include <linux/fcntl.h>
#include <linux/ide.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>

#define MISCBEEP_NAME "miscbeep"
#define MISCBEEP_MINOR  144
#define BEEPOFF  0
#define BEEPON   1

/* miscbeep设备结构体 */
struct miscbeep_dev {
    struct device_node *nd; /* 设备节点 */
    int beep_gpio;          /* beep gpio */
};

struct miscbeep_dev miscbeep;

static int miscbeep_open(struct inode *inode, struct file *filp)
{
    filp->private_data = &miscbeep;
    return 0;
}

static int miscbeep_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static ssize_t miscbeep_write(struct file *filp, const char __user *buf,
			 size_t count, loff_t *ppos)
{

    int ret;
    unsigned char databuf[1];
    struct miscbeep_dev *dev = filp->private_data;

    ret = copy_from_user(databuf, buf, count);
    if(ret < 0) {
        return -EINVAL;
    }

    if(databuf[0] == BEEPON) {
        gpio_set_value(dev->beep_gpio, 0); /* 打开锋鸣器 */ 
    } else if(databuf[0] == BEEPOFF) {
        gpio_set_value(dev->beep_gpio, 1); /* 关闭锋鸣器 */ 
    }

    return 0;
}

/* 字符设备操作集 */
struct file_operations miscbeep_fops = {
    .owner = THIS_MODULE,
    .open = miscbeep_open,
    .release = miscbeep_release,
    .write = miscbeep_write,
};

/* miscdevice结构体 */
static struct miscdevice beep_miscdev = {
    .minor = MISCBEEP_MINOR,
    .name = MISCBEEP_NAME,
    .fops = &miscbeep_fops,
};

static int miscbeep_probe(struct platform_device *dev)
{
    int ret = 0;
    /* 1、初始化锋鸣器IO */
    miscbeep.nd =  dev->dev.of_node;

    miscbeep.beep_gpio = of_get_named_gpio(miscbeep.nd, "beep-gpios", 0);
    if(miscbeep.beep_gpio < 0) {
        ret = -EINVAL;
        goto fail_findgpio;
    }

    ret = gpio_request(miscbeep.beep_gpio, "beep-gpio");
    if(ret) {
        printk("can't request %d gpio!\r\n", miscbeep.beep_gpio);
        ret = -EINVAL;
        goto fail_findgpio;
    }

    ret = gpio_direction_output(miscbeep.beep_gpio, 1);/* 输出，默认高电平 */
    if(ret < 0) {
        goto fail_setoutput;
    }

    /* 2、misc驱动注册 */
    ret = misc_register(&beep_miscdev);
    if(ret < 0) {
        goto fail_setoutput;
    }

    return 0;

fail_setoutput:
    gpio_free(miscbeep.beep_gpio);
fail_findgpio:
    return ret;
}

static int miscbeep_remove(struct platform_device *dev)
{
    gpio_set_value(miscbeep.beep_gpio, 1); /* 拉高，关闭BEEP */
    gpio_free(miscbeep.beep_gpio); /* 释放GPIO */

    gpio_free(miscbeep.beep_gpio); /* 释放GPIO */
    return 0;
}

/* platform匹配表 */
static const struct of_device_id beep_of_match[] = {
    {.compatible = "alientek,beep"},
    {/* Sentinel */},
};


static struct platform_driver miscbeep_driver = {
    .driver={
        .name = "imx6ull-beep",
        .of_match_table=beep_of_match,//**设备树匹配表 */
    },
    .probe = miscbeep_probe,
    .remove = miscbeep_remove,
};
/*
 设备加载
 */
static int __init miscbeep_init(void)
{
    /* 注册platform设备 */
    return platform_driver_register(&miscbeep_driver);
}

/* 
 设备卸载
 */
static void __exit miscbeep_exit(void)
{
    //**卸载platform */
    platform_driver_unregister(&miscbeep_driver);
}

module_init(miscbeep_init);
module_exit(miscbeep_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("abcooxj");