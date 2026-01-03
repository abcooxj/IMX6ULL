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

#define LED_MAJOR  200
#define LED_NAME   "led"

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

/*
 * @description		: LED打开/关闭
 * @param - sta 	: LEDON(0) 打开LED，LEDOFF(1) 关闭LED
 * @return 			: 无
 */
void led_switch(u8 sta)
{
	u32 val = 0;
	if(sta == LEDON) {
		val = readl(GPIO1_DR);
		val &= ~(1 << 3);	
		writel(val, GPIO1_DR);
	}else if(sta == LEDOFF) {
		val = readl(GPIO1_DR);
		val|= (1 << 3);	
		writel(val, GPIO1_DR);
	}	
}

static int led_open(struct inode *inode,struct file *filp)
{
    return 0;
}

static int led_release(struct inode *inode,struct file *filp)
{
    return 0;
}

/*
 * @description		: 向设备写数据 
 * @param - filp 	: 设备文件，表示打开的文件描述符
 * @param - buf 	: 要写给设备写入的数据
 * @param - cnt 	: 要写入的数据长度
 * @param - offt 	: 相对于文件首地址的偏移
 * @return 			: 写入的字节数，如果为负值，表示写入失败
 */
static ssize_t led_write(struct file *filp, const char __user *buf, size_t count, loff_t *offt)
{
	int retvalue;
	unsigned char databuf[1];
	unsigned char ledstat;

	retvalue = copy_from_user(databuf, buf, count);
	if(retvalue < 0) {
		printk("kernel write failed!\r\n");
		return -EFAULT;
	}

	ledstat = databuf[0];		/* 获取状态值 */

	if(ledstat == LEDON) {	
		led_switch(LEDON);		/* 打开LED灯 */
	} else if(ledstat == LEDOFF) {
		led_switch(LEDOFF);	/* 关闭LED灯 */
	}
	return 0;
}

//**字符设备操作集 */
static const struct file_operations led_fops={
    .owner= THIS_MODULE,
    .write= led_write,
    .open= led_open,
    .release= led_release,
};

//**入口 */
static int __init led_init(void)
{
    int ret=0;
    u32 val=0;
    //**1.初始化LED灯 */
    IMX6U_CCM_CCGR1=ioremap(CCM_CCGR1_BASE,4);
    SW_MUX_GPIO1_IO03=ioremap(SW_MUX_GPIO1_IO03_BASE,4);
    SW_PAD_GPIO1_IO03=ioremap(SW_PAD_GPIO1_IO03_BASE,4);
    GPIO1_DR=ioremap(GPIO1_DR_BASE,4);
    GPIO1_GDIR=ioremap(GPIO1_GDIR_BASE,4);

    //**2. 初始化*/
    val=readl(IMX6U_CCM_CCGR1);
    val &= ~(3<<26);/**先清除以前的配置bit26,27 */
    val |=3<<26;//**bit26,27置为1 */
    writel(val,IMX6U_CCM_CCGR1);

    writel(5,SW_MUX_GPIO1_IO03);//**设置复用 */
    writel(0x10B0, SW_PAD_GPIO1_IO03);//**设置电气属性 */

    val=readl(GPIO1_GDIR);
    val &= ~(1 << 3);	/* 清除以前的设置 */
    val |=1<<3;//***bit3置为1，设置为输出 */
    writel(val,GPIO1_GDIR);

    val = readl(GPIO1_DR);
	val |= (1 << 3);	
	writel(val, GPIO1_DR);

    //**1. 注册字符设备 */
    ret=register_chrdev(LED_MAJOR,LED_NAME,&led_fops);
    if(ret<0)
    {
        printk("register chardev failed!\r\n");
        return -EIO;
    }
    printk("led init\r\n");
    return 0;
}
static void __exit led_exit(void)
{
    //**1.取消地址映射 */
    iounmap(IMX6U_CCM_CCGR1);
    iounmap(SW_MUX_GPIO1_IO03);
    iounmap(SW_PAD_GPIO1_IO03);
    iounmap(GPIO1_DR);
    iounmap(GPIO1_GDIR);

    //**注销字符设备 */
    unregister_chrdev(LED_MAJOR,LED_NAME);
    printk("led exit\r\n");
}

//**注册驱动加载和卸载 */
module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abcooxj");