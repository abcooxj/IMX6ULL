#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define NEWCHRLED_NAME   "newchrled"
#define NEWCHRLED_COUNT 1

#define LEDOFF 	0				/* 关灯 */
#define LEDON 	1				/* 开灯 */

/* 寄存器物理地址 */
#define CCM_CCGR1_BASE				(0X020C406C)	
#define SW_MUX_GPIO1_IO03_BASE		(0X020E0068)
#define SW_PAD_GPIO1_IO03_BASE		(0X020E02F4)
#define GPIO1_DR_BASE				(0X0209C000)
#define GPIO1_GDIR_BASE				(0X0209C004)


/* 映射后的寄存器虚拟地址指针 */
static void __iomem *IMX6U_CCM_CCGR1;
static void __iomem *SW_MUX_GPIO1_IO03;
static void __iomem *SW_PAD_GPIO1_IO03;
static void __iomem *GPIO1_DR;
static void __iomem *GPIO1_GDIR;


//**LED设备结构体 */
struct newchrled_dev
{
    struct cdev cdev; //**字符设备 */
    dev_t devid;    //**设备号 */
    struct class *class;//**类 */
    struct device *device; //** 设备*/
    int major;      //**主设备号 */
    int minor;      //**次设备号 */
};

struct newchrled_dev newchrled; //**led设备 */

//**LED灯打开/关闭 */
static void led_switch(u8 sta)
{
    u32 val=0;
    if(sta==LEDON)
    {
        val=readl(GPIO1_DR);
        val &= ~(1<<3);
        writel(val,GPIO1_DR);
    }
    else if (sta==LEDOFF)
    {
        val=readl(GPIO1_DR);
        val |=(1<<3);//**bit3清零，打开LED灯 */
        writel(val,GPIO1_DR);
    }
}

static int newchrled_open(struct inode *inode,struct file *filp)
{
    filp->private_data=&newchrled;//***设置私有数据 */
    return 0;
}

static int newchrled_release(struct inode *inode,struct file *filp)
{
    //struct newchrled_dev *dev = (struct newchrled_dev *)filp->private_data;
    return 0;
}

static ssize_t newchrled_write(struct file *filp,const char __user *buf,size_t count,loff_t *ppos)
{
    int retvalue;
    unsigned char databuf[1];
    retvalue=copy_from_user(databuf,buf,count);
    if(retvalue<0)
    {
        printk("kernel write failed!\r\n");
        return -EFAULT;
    }

    //**判断开灯还是关灯 */
    led_switch(databuf[0]);
    return 0;
}

static const struct file_operations newchrled_fops=
{
    .owner= THIS_MODULE,
    .write=newchrled_write,
    .open=newchrled_open,
    .release=newchrled_release,
};

//**入口 */
static int __init newchrled_init(void)
{
    int ret=0;
    unsigned int val=0;
    printk("newchrled init\r\n");
    //**1.初始化LED */
    /* 1、寄存器地址映射 */
    IMX6U_CCM_CCGR1 = ioremap(CCM_CCGR1_BASE, 4);
    SW_MUX_GPIO1_IO03 = ioremap(SW_MUX_GPIO1_IO03_BASE, 4);
    SW_PAD_GPIO1_IO03 = ioremap(SW_PAD_GPIO1_IO03_BASE, 4);
    GPIO1_DR = ioremap(GPIO1_DR_BASE, 4);
    GPIO1_GDIR = ioremap(GPIO1_GDIR_BASE, 4);
    /* 2、使能 GPIO1 时钟 */
    val = readl(IMX6U_CCM_CCGR1);
    val &= ~(3 << 26); /* 清楚以前的设置 */
    val |= (3 << 26); /* 设置新值 */
    writel(val, IMX6U_CCM_CCGR1);

    writel(5, SW_MUX_GPIO1_IO03);
    /* 寄存器 SW_PAD_GPIO1_IO03 设置 IO 属性 */
    writel(0x10B0, SW_PAD_GPIO1_IO03);
    /* 4、设置 GPIO1_IO03 为输出功能 */
    val = readl(GPIO1_GDIR);
    //val &= ~(1 << 3); /* 清除以前的设置 */
    val |= (1 << 3); /* 设置为输出 */
    writel(val, GPIO1_GDIR);
    /* 5、默认关闭 LED */
    val = readl(GPIO1_DR);
    val |= (1 << 3);
    writel(val, GPIO1_DR);

    //**2.注册字符设备 */
    if(newchrled.major)//**给定主设备号 */
    {
        newchrled.devid =MKDEV(newchrled.major,0);
        ret=register_chrdev_region(newchrled.devid,NEWCHRLED_COUNT,NEWCHRLED_NAME);
    }
    else//**没有给定主设备号 */
    {
        ret=alloc_chrdev_region(&newchrled.devid,0,NEWCHRLED_COUNT,NEWCHRLED_NAME);
        newchrled.major=MAJOR(newchrled.devid);
        newchrled.minor=MINOR(newchrled.devid);
    }
    if(ret<0)
    {
        printk("newchrled chrdev_region err!\r\n");
    }
    printk("newchrled major=%d,minor=%d\r\n",newchrled.major,newchrled.minor);

    //**3.注册字符设备 */
    newchrled.cdev.owner=THIS_MODULE;
    cdev_init(&newchrled.cdev,&newchrled_fops);
    ret=cdev_add(&newchrled.cdev,newchrled.devid,NEWCHRLED_COUNT);

    //** 4。自动创建设备节点*/
    newchrled.class=class_create(THIS_MODULE,NEWCHRLED_NAME);
    if(IS_ERR(newchrled.class))
        return PTR_ERR(newchrled.class);

    newchrled.device=device_create(newchrled.class,NULL,newchrled.devid,NULL,NEWCHRLED_NAME);
    if(IS_ERR(newchrled.device))
        return PTR_ERR(newchrled.device);

    return 0;
}

//**出口 */
static void __exit newchrled_exit(void)
{
    unsigned int val=0;
    printk("newchrled exit\r\n");
    
    val=readl(GPIO1_DR);
    val |= 1<<3;
    writel(val,GPIO1_DR);

    /* 取消映射 */
    iounmap(IMX6U_CCM_CCGR1);
    iounmap(SW_MUX_GPIO1_IO03);
    iounmap(SW_PAD_GPIO1_IO03);
    iounmap(GPIO1_DR);
    iounmap(GPIO1_GDIR);

    //***1.删除字符设备 */
    cdev_del(&newchrled.cdev);
    //**2.注销设备号 */
    unregister_chrdev_region(newchrled.devid,NEWCHRLED_COUNT);

    //**3.摧毁设备 */
    device_destroy(newchrled.class,newchrled.devid);

    //**4.摧毁类 */
    class_destroy(newchrled.class);
}


//**注册和卸载驱动 */
module_init(newchrled_init);
module_exit(newchrled_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abcooxj");