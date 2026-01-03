#include "bsp_delay.h"
#include "bsp_int.h"
#include "bsp_led.h"

//*延时初始化函数
void delay_init(void)
{
    GPT1->CR=0;

    GPT1->CR=1<<15;
    while ((GPT1->CR>>15)&0X01);
    
    /*
   	 * GPT的CR寄存器,GPT通用设置
   	 * bit22:20	000 输出比较1的输出功能关闭，也就是对应的引脚没反应
     * bit9:    0   Restart模式,当CNT等于OCR1的时候就产生中断
     * bit8:6   001 GPT时钟源选择ipg_clk=66Mhz,Restart模式
     * bit
  	 */
	GPT1->CR |= (1<<1) |(1<<6);

	/*
     * GPT的PR寄存器，GPT的分频设置
     * bit11:0  设置分频值，设置为0表示1分频，
     *          以此类推，最大可以设置为0XFFF，也就是最大4096分频
	 */
	GPT1->PR = 65;	/* 设置为65，即66分频，因此GPT1时钟为66M/(65+1)=1MHz */

    /*
      * GPT的OCR1寄存器，GPT的输出比较1比较计数值，
      *	GPT的时钟为1Mz，那么计数器每计一个值就是就是1us。
      * 为了实现较大的计数，我们将比较值设置为最大的0XFFFFFFFF,
      * 这样一次计满就是：0XFFFFFFFFus = 4294967296us = 4295s = 71.5min
      * 也就是说一次计满最多71.5分钟，存在溢出
	  */
	GPT1->OCR[0] = 0XFFFFFFFF;

	GPT1->CR |= 1<<0;			//使能GPT1

#if 0
	 /*
      * GPT的OCR1寄存器，GPT的输出比较1比较计数值，
      *	GPT的时钟为1Mz，那么计数器每计一个值就是就是1us。
      * 为了实现较大的计数，我们将比较值设置为最大的0XFFFFFFFF,
      * 这样一次计满就是：0XFFFFFFFFus = 4294967296us = 4295s = 71.5min
      * 也就是说一次计满最多71.5分钟，存在溢出
	  */
	GPT1->OCR[0] = 1000000/2;

	GPT1->IR |= 1<<0;			//使能GPT1

    //*设置GIC
    GIC_EnableIRQ(GPT1_IRQn);

	system_register_irqhandler(GPT1_IRQn, gpt1_irqhandler, NULL);	//注册中断服务函数	

    GPT1->CR|=1<<0;//*打开GPT1
#endif
}

#if 0
/* GPT1中断服务函数 */
void gpt1_irqhandler(void)
{ 
	static unsigned char state = 0;

	/*
     * GPT的SR寄存器，状态寄存器
     * bit2： 1 输出比较1发生中断
	 */
	if(GPT1->SR & (1<<0)) 
	{
        state = !state;
		led_switch(LED0, state);
	}
	
	GPT1->SR |= 1<<0; /* 清除中断标志位 */
}
#endif

 
/*
 * @description		: 微秒(us)级延时
 * @param - value	: 需要延时的us数,最大延时0XFFFFFFFFus
 * @return 			: 无
 */
void delay_us(unsigned    int usdelay)
{
	unsigned long oldcnt,newcnt;
	unsigned long tcntvalue = 0;	/* 走过的总时间  */

	oldcnt = GPT1->CNT;
	while(1)
	{
		newcnt = GPT1->CNT;
		if(newcnt != oldcnt)
		{
			if(newcnt > oldcnt)		/* GPT是向上计数器,并且没有溢出 */
				tcntvalue += newcnt - oldcnt;
			else  					/* 发生溢出    */
				tcntvalue += 0XFFFFFFFF-oldcnt + newcnt;
			oldcnt = newcnt;
			if(tcntvalue >= usdelay)/* 延时时间到了 */
			break;			 		/*  跳出 */
		}
	}
}//!!!使用abs函数
         
/*
 * @description		: 毫秒(ms)级延时
 * @param - msdelay	: 需要延时的ms数
 * @return 			: 无
 */
void delay_ms(unsigned	 int msdelay)
{
	int i = 0;
	for(i=0; i<msdelay; i++)
	{
		delay_us(1000);
	}
}

//*短延时
void delay_short(volatile unsigned int n)
{
    while(n--)
    {

    }
}

//****延时，一次循环大概是1ms,在主频为396MHZ时
//****n:延时ms数
void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0x7ff);
    }
}
