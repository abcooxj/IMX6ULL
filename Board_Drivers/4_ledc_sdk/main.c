#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"


//*使能外设时钟
void clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0XFFFFFFFF;
    CCM->CCGR2 = 0XFFFFFFFF;
    CCM->CCGR3 = 0XFFFFFFFF;
    CCM->CCGR4 = 0XFFFFFFFF;
    CCM->CCGR5 = 0XFFFFFFFF;
    CCM->CCGR6 = 0XFFFFFFFF;
}

//*初始化LED
void led_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);

    //IOMUX_SW_MUX->GPIO1_IO03=0X5; //*复用为GPIO1_IO03
    //IOMUX_SW_PAD->GPIO1_IO03=0X10B0;//*设置GPIO1_IO03电气属性

    //*GPIO初始化
    GPIO1->GDIR=0X8;        //*设置为输出
    GPIO1->DR=0X0;           //*打开LED灯
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

//*打开LED灯
void led_on(void)
{
    GPIO1->DR &= ~(1<<3); //*bit3清零
}

//*关闭LED灯
void led_off(void)
{
    GPIO1->DR |= (1<<3);//*bit3置为1
}

//*跳转到C语言main函数 */
int main(void)
{
    clk_enable();    //*使能外设时钟
    led_init();      //*初始化LED
    //*初始化LED*/
 
    //*设置LED闪烁*/
    while(1)
    {
       led_on();
       delay(1000);

       led_off();
       delay(1000);
    }
    return 0;
}



