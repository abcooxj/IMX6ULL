#include "bsp_backlight.h"
#include "bsp_int.h"
#include "stdio.h"

/* 背光设备 */
struct backlight_dev_struc backlight_dev;

//**初始化背光 */
void backlight_init(void)
{
    unsigned char i = 0;

    //**1.IO初始化 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_PWM1_OUT, 0); /* 复用为PWM1_OUT */
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_PWM1_OUT, 0XB090);

    //**2.PWM初始化 */
    PWM1->PWMCR=0;//**清零 */
    PWM1->PWMCR |= (1 << 26) | (1 << 16) | (65 << 4);

	/* 设置PWM周期为1000,那么PWM频率就是1M/1000 = 1KHz。 */
	pwm1_setperiod_value(1000);

	//*3. 设置占空比，默认50%占空比   ,写四次是因为有4个FIFO */
	backlight_dev.pwm_duty = 50;
	for(i = 0; i < 4; i++)
	{
		pwm1_setduty(backlight_dev.pwm_duty);	
	}
	
	//*4. 使能FIFO空中断，设置寄存器PWMIR寄存器的bit0为1 */
	PWM1->PWMIR |= 1 << 0;
	system_register_irqhandler(PWM1_IRQn, (system_irq_handler_t)pwm1_irqhandler, NULL);	/* 注册中断服务函数 */
	GIC_EnableIRQ(PWM1_IRQn);	/* 使能GIC中对应的中断 */
	PWM1->PWMSR = 0;			/* PWM中断状态寄存器清零 */
	
	//pwm1_enable();				/* 使能PWM1 */
    PWM1->PWMCR |= 1 << 0;          /* 使能PWM1 */
}

/*
 * @description	: 使能PWM
 * @param		: 无
 * @return 		: 无
 */
//void pwm1_enable(void)
//{
//	PWM1->PWMCR |= 1 << 0;	 
//}


//**设置PR寄存器 */
void pwm1_setperiod_value(unsigned int value)
{
    unsigned int regvalue;
    if(value < 2)
		regvalue = 2;
	else 
		regvalue = value - 2;
	PWM1->PWMPR = (regvalue & 0XFFFF);
}

//**设置占空比duty=0-100 */
void pwm1_setduty(unsigned char duty)
{
	unsigned short preiod;
	unsigned short sample;

	backlight_dev.pwm_duty = duty;
	preiod = PWM1->PWMPR + 2;
	sample = (unsigned short)(preiod * backlight_dev.pwm_duty / 100.0f);
	//pwm1_setsample_value(sample);
    PWM1->PWMSAR=(sample&0xffff);
}

//**中断处理函数 */
//void pwm1_irqhandler(unsigned int gicciar,void *param)
void pwm1_irqhandler(void)
{

	if(PWM1->PWMSR & (1 << 3)) 	/* FIFO为空中断 */
	{
		/* 将占空比信息写入到FIFO中,其实就是设置占空比 */
		pwm1_setduty(backlight_dev.pwm_duty); 
		PWM1->PWMSR |= (1 << 3); /* 写1清除中断标志位 */ 
	}
}