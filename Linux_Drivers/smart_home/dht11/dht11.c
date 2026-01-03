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
#include <linux/poll.h>
#include <linux/fcntl.h>
#include <linux/ide.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/ktime.h>

#define DHT11_CNT  1
#define DHT11_NAME  "dht11"

/*dht11设备结构体*/
struct dht11_dev {
    dev_t devid;
    int major;
    int minor;
    struct cdev cdev;
    struct class *class;
    struct device *device;
    struct device_node *nd;
    int dht11_gpio;
};

struct dht11_dev dht11;

int us_array[40];
int time_array[40];
int us_index;

/*复位信号*/
void dht11_reset(void)
{
    gpio_direction_output(dht11.dht11_gpio, 1);//主机发出信号，将电平拉高，进行等待
}

/*起始信号*/
void dht11_start(void)
{
    mdelay(30);
    gpio_set_value(dht11.dht11_gpio, 0);
    mdelay(30);
    gpio_set_value(dht11.dht11_gpio, 1);
    udelay(40);
    //将引脚配置为输入模式，准备响应DHT11，接收数据
    gpio_direction_input(dht11.dht11_gpio);
    udelay(2);
}

//响应DHT11的响应信号
static int dht11_wait_for_ready(void)
{
    int timercount=200; //等待DHT11响应信号，如果超过200ms，则认为DHT11没有响应,超时时间

    //循环等待低电平，当电平引脚为1且timerout不为0时一直循环等待
    while(gpio_get_value(dht11.dht11_gpio)==0 && --timercount)
    {
        udelay(1);
    }
    if(timercount==0)
    {
        return -1;
    }

    //等待高电平
    while(gpio_get_value(dht11.dht11_gpio)==1 && --timercount)
    {
        udelay(1);
    }
    if(timercount==0)
    {
        return -1;
    }

    //等待低电平
    while (gpio_get_value(dht11.dht11_gpio) == 0 && --timercount)
    {
        udelay(1);
    }
    if (timercount == 0)
    {
        return -1;
    }

    return 0;
}
static int dht11_read_byte(unsigned char *buf)
{
    int i;
    unsigned char data=0;
    int timeout_us=200;// 定义一个整型变量timeout_us，并初始化为200，用于设置超时计数
    u64 pre,last;//定义两个64位无符号整数变量pre和last，用于记录时间
    int ns;//存储时间差
    

    for(i=0;i<8;i++)//循环8次，因为一个字节有8位
    {
        //目前处于低电平
        //现在等待高电平
        timeout_us = 400; // 重置超时计数为400微秒
        while (!gpio_get_value(dht11.dht11_gpio)&& --timeout_us)
        {
            udelay(1);
        }
        if (!timeout_us)
        {
            printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
            return -1;
        }

        //等待低电平，累加高电平的时间
        timeout_us = 20000000; // 设置超时计数为一个非常大的值，以便能够累加高电平的时间
        pre=ktime_get_ns(); // 记录当前时间
        while (gpio_get_value(dht11.dht11_gpio) && --timeout_us)
        {
            //udelay(1);
            //timeout_usus++;
        }
        last = ktime_get_boot_ns(); // 获取当前时间（纳秒）
        //printk("udelay 1000 ns = %s\n", last-pre); // 打印高电平持续的时间，单位为纳秒

        ns = last - pre; // 计算高电平持续的时间（纳秒）
        if (!timeout_us) // 如果超时，返回-1
        {
            return -1;
        }
        us_array[us_index] = ns;                        // 将高电平持续的时间存储到数组中
        time_array[us_index++] = 20000000 - timeout_us; // 将剩余的超时计数存储到另一个数组中5
        if (ns > 40000)                                 // 如果高电平持续的时间大于40微秒，表示接收到的是数据位1
        {
            /* get bit 1 */
            data = (data << 1) | 1; // 将data左移一位，并将最低位置为1
        }
        else
        {
            /* get bit 0 */
            data = (data << 1) | 0; // 将data左移一位，并将最低位置为0
        }
    }
    *buf = data; // 将读取到的数据存储到传入的缓冲区中
    return 0;    // 返回0表示成功
}

static int dht11_open(struct inode *inode, struct file *filp)
{
    printk("dht11_open\r\n");
    return 0;
}

static int dht11_release(struct inode *inode, struct file *filp)
{
    printk("dht11_release\r\n");
    return 0;
}

static ssize_t dht11_write(struct file *filp, const char __user *buf,size_t count, loff_t *ppos)
{
    printk("dht11_write\r\n");
    return 0;
}

static ssize_t dht11_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
    unsigned long flags;
    int i, err;
    unsigned char data[5];
    us_index = 0; // 重置us_index变量，可能用于记录时间或状态

    if (count != 4)     // 检查用户请求的数据大小是否为4字节
        return -EINVAL; // 如果不是，返回无效参数错误

    local_irq_save(flags); // 保存当前的中断标志并关闭中断

    /* 1. 发送高脉冲启动DHT11 */
    dht11_reset(); // 重置DHT11传感器
    dht11_start(); // 启动DHT11传感器

    /* 2. 等待DHT11就绪 */
    if (dht11_wait_for_ready()) // 等待DHT11传感器准备就绪
    {
        local_irq_restore(flags);// 如果DHT11没有就绪，恢复中断
        printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__); // 打印错误信息
        return -EAGAIN;                                              // 返回错误，表示需要重试
    }

    /* 3. 读5字节数据 */
    /*5位的字节分别是湿度整数部分（1字节），湿度小数部分（1字节）温度整数部分（1字节）温度小数部分（1字节）校验和（1字节）*/
    /*Byte 1: 湿度整数部分
     *Byte 2: 湿度小数部分
     *Byte 3: 温度整数部分
     *Byte 4: 温度小数部分
     *Byte 5: 校验和（Byte 1 + Byte 2 + Byte 3 + Byte 4）
     */
    for (i = 0; i < 5; i++) // 循环读取5个字节的数据
    {
        if (dht11_read_byte(&data[i])) // 读取一个字节的数据
        {
            local_irq_restore(flags);// 如果读取失败，恢复中断
            printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__); // 打印错误信息
            return -EAGAIN;                                              // 返回错误，表示需要重试
        }
    }

    dht11_reset(); // 读取完成后重置DHT11传感器

    local_irq_restore(flags); // 恢复中断
                              /* 4. 根据校验码验证数据 */
    if (data[4] != (data[0] + data[1] + data[2] + data[3])) // 校验数据
    {
        printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__); // 打印错误信息
        return -1;                                                   // 如果校验失败，返回错误
    }

    /* 5. copy_to_user */
    /* data[0]/data[1] : 湿度 */
    /* data[2]/data[3] : 温度 */
    err = copy_to_user(buf, data, 4); // 将数据复制到用户空间缓冲区
    return 4;                         // 返回读取的字节数
}

    /* 操作集 */
    static const struct file_operations dht11_fops = {
        .owner = THIS_MODULE,
        .write = dht11_write,
        .read = dht11_read,
        .open = dht11_open,
        .release = dht11_release,
    };

static int dht11_probe(struct platform_device *dev)
{
   int ret=0;
    printk("dht11_probe\r\n");
    /*1.注册字符设备驱动*/
    dht11.major = 0;
    if(dht11.major) /*给定主设备号*/
    {
        dht11.devid = MKDEV(dht11.major, 0);
        register_chrdev_region(dht11.devid, DHT11_CNT, DHT11_NAME);
    }
    else /*没给定设备号*/
    {
        alloc_chrdev_region(&dht11.devid, 0, DHT11_CNT, DHT11_NAME);
        dht11.major = MAJOR(dht11.devid);
        dht11.minor = MINOR(dht11.devid);
    }
    printk("dht11 major = %d, minor = %d\r\n",dht11.major, dht11.minor);

    /*2.初始化cdev*/
    dht11.cdev.owner = THIS_MODULE;
    cdev_init(&dht11.cdev, &dht11_fops);

    /*3.添加cdev*/
    cdev_add(&dht11.cdev, dht11.devid, DHT11_CNT);

    /*4.创建类*/
    dht11.class = class_create(THIS_MODULE, DHT11_NAME);
    if (IS_ERR(dht11.class)) 
    {
        return PTR_ERR(dht11.class);
    }

    /*5.创建设备*/
    dht11.device = device_create(dht11.class, NULL, dht11.devid, NULL, DHT11_NAME);
    if (IS_ERR(dht11.device))
    {
        return PTR_ERR(dht11.device);
    }

    /*1.获取设备节点*/
    dht11.nd = dev->dev.of_node;

    /*2.获取DHT11所对应的GPIO*/
    dht11.dht11_gpio = of_get_named_gpio(dht11.nd, "dht11-gpios", 0);
    if (dht11.dht11_gpio<0)
    {
        printk("get gpio failed\r\n");
        ret=-EINVAL;
        goto fail_findnode;
    }
    printk("dht11.gpio = %d\r\n",dht11.dht11_gpio);

    /*3.申请IO*/
    ret = gpio_request(dht11.dht11_gpio, "dht11");
    if (ret)
    {
        printk("Failed to request the dht11 gpio\r\n");
        ret = -EINVAL;
        goto fail_findnode;
    }

    /*4.使用IO,设置为输出*/
    ret = gpio_direction_output(dht11.dht11_gpio, 1);
    if (ret)
    {
        goto fail_setoutput;
    }

    return 0;

fail_setoutput:
    gpio_free(dht11.dht11_gpio);
fail_findnode:
    return ret;
}

static int dht11_remove(struct platform_device *dev)
{
    printk("dht11_remove\r\n");

    /*注销字符设备驱动*/
    cdev_del(&dht11.cdev);
    unregister_chrdev_region(dht11.devid, DHT11_CNT);

    device_destroy(dht11.class, dht11.devid);
    class_destroy(dht11.class);

    /*释放IO*/
    gpio_free(dht11.dht11_gpio);

    return 0;
}

struct of_device_id dht11_of_match[] = {
    {.compatible = "dht11"},
    {/* sentinel */},
};

struct platform_driver dht11_driver = {
    .driver = {
        .name = "dht11",                  /* 无设备树和设备进行匹配，驱动名字 */
        .of_match_table = dht11_of_match, /* 设备树匹配表 */

    },
    .probe = dht11_probe,
    .remove = dht11_remove,
};

static int __init dht11_init(void)
{
    printk("dht11_init\r\n");
    return platform_driver_register(&dht11_driver);
} 

static void __exit dht11_exit(void)
{
    printk("dht11_exit\r\n");
    platform_driver_unregister(&dht11_driver);
}

//**注册驱动加载和卸载 */
module_init(dht11_init);
module_exit(dht11_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("abcooxj");