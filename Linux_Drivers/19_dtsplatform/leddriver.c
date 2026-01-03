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

#define GPIOLED_CNT     1
#define GPIOLED_NAME    "dtsplatled"
#define LEDOFF          0
#define LEDON           1

/* gpioled设备结构体 */
struct gpioled_dev{
    dev_t devid;
    int major;
    int minor;
    struct cdev cdev;
    struct class *class;
    struct device *device;
    struct device_node *nd;
    int led_gpio;
};

struct gpioled_dev gpioled; /* LED */

static int led_open(struct inode *inode, struct file *filp)
{
    filp->private_data = &gpioled;
    return 0;
}

static int led_release(struct inode *inode, struct file *filp)
{
    
    return 0;
}

static ssize_t led_write(struct file *filp, const char __user *buf,
			 size_t count, loff_t *ppos)
{
    int ret;
    unsigned char databuf[1];
    struct gpioled_dev *dev = filp->private_data;

    ret = copy_from_user(databuf, buf, count);
    if(ret < 0) {
        return -EINVAL;
    }

    if(databuf[0] == LEDON) {
        gpio_set_value(dev->led_gpio, 0); 
    } else if(databuf[0] == LEDOFF) {
        gpio_set_value(dev->led_gpio, 1); 
    }

    return 0;
}

/* 操作集 */
static const struct file_operations led_fops = {
    .owner		=	THIS_MODULE,
	.write		=	led_write,
	.open		=	led_open,
	.release	=	led_release,
};

static int led_probe(struct platform_device *dev)
{
    int ret = 0;

    printk("led_probe\r\n");

    /* 注册字符设备驱动 */
    gpioled.major = 0;
    if(gpioled.major) { /* 给定主设备号 */
        gpioled.devid = MKDEV(gpioled.major, 0);
        register_chrdev_region(gpioled.devid, GPIOLED_CNT, GPIOLED_NAME);
    } else {            /* 没给定设备号 */
        alloc_chrdev_region(&gpioled.devid, 0, GPIOLED_CNT, GPIOLED_NAME);
        gpioled.major = MAJOR(gpioled.devid);
        gpioled.minor = MINOR(gpioled.devid);
    }
    printk("gpioled major = %d, minor = %d\r\n", gpioled.major, gpioled.minor);

    /* 2,初始化cdev */
    gpioled.cdev.owner = THIS_MODULE;
    cdev_init(&gpioled.cdev, &led_fops);

    /* 3,添加cdev */
    cdev_add(&gpioled.cdev, gpioled.devid, GPIOLED_CNT);

    /* 4、创建类 */
    gpioled.class = class_create(THIS_MODULE, GPIOLED_NAME);
    if(IS_ERR(gpioled.class)) {
        return PTR_ERR(gpioled.class);
    }

    /* 5,创建设备  */
    gpioled.device = device_create(gpioled.class, NULL, gpioled.devid, NULL, GPIOLED_NAME);
    if(IS_ERR(gpioled.device)) {
        return PTR_ERR(gpioled.device);
    }

    /* 1，获取设备节点 */
#if 0
    gpioled.nd = of_find_node_by_path("/gpioled");
    if(gpioled.nd == NULL) {
        ret = -EINVAL;
        goto fail_findnode;
    }
#endif
    gpioled.nd = dev->dev.of_node; 
  
    /* 2, 获取LED所对应的GPIO */
    gpioled.led_gpio = of_get_named_gpio(gpioled.nd, "led-gpios", 0);
    if(gpioled.led_gpio < 0) {
        printk("can't find led gpio\r\n");
        ret = -EINVAL;
        goto fail_findnode;
    }
    printk("led gpio num = %d\r\n", gpioled.led_gpio);

    /* 3,申请IO */
    ret = gpio_request(gpioled.led_gpio, "led-gpio");
	if (ret) {
		printk("Failed to request the led gpio\r\n");
		ret = -EINVAL;
        goto fail_findnode;
	}

    /* 4,使用IO，设置为输出 */
    ret = gpio_direction_output(gpioled.led_gpio, 1);
	if (ret) {
		goto fail_setoutput;
	}

    /* 5,输出底电平，点亮LED灯*/
    gpio_set_value(gpioled.led_gpio, 0);

    return 0;

fail_setoutput:
    gpio_free(gpioled.led_gpio);
fail_findnode:
    return ret;
}

static int led_remove(struct platform_device *dev)
{
  printk("led_remove\r\n");

      /* 关灯 */
      gpio_set_value(gpioled.led_gpio, 1);

      /* 注销字符设备驱动 */
      cdev_del(&gpioled.cdev);
      unregister_chrdev_region(gpioled.devid, GPIOLED_CNT);
  
      device_destroy(gpioled.class, gpioled.devid);
      class_destroy(gpioled.class);
  
      /* 释放IO */
      gpio_free(gpioled.led_gpio);
  
      return 0;
 
}

struct of_device_id led_of_match[] = {
  { .compatible = "alientek,gpioled", },
  { /* sentinel */ },
};

//**platform驱动结构体 */
static struct platform_driver led_driver = {
  .driver = {
    .name = "imx6ull-led",//**驱动和设备 */
    .of_match_table = led_of_match,//**设备树匹配表 */
  },
  .probe = led_probe,
  .remove = led_remove,
};

/*
 设备加载
 */
static int __init leddriver_init(void)
{
    /* 注册platform设备 */
    return platform_driver_register(&led_driver);
}

/* 
 设备卸载
 */
static void __exit leddriver_exit(void)
{
    //**卸载platform */
    platform_driver_unregister(&led_driver);
}

module_init(leddriver_init);
module_exit(leddriver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("abcooxj");