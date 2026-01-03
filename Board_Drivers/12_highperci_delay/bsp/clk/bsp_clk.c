#include "bsp_clk.h"

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

//*初始化时钟
void imx6u_clkinit(void)
{
    unsigned int reg=0;

    //*初始化6U的主频为528MHZ
    if(((CCM->CCSR>>2)&0X1)==0)//**当前时钟使用pll_main_clk也就是pll1 */
    {
        CCM->CCSR &= ~(1<<8);//**设置step_clk=osc_clk=24MHZ */
        CCM->CCSR |= (1<<2);//**pll1_main_clk=step_clk=24MHZ */
    }
    //***设置PLL1=1056MHZ */
    CCM_ANALOG->PLL_ARM= (1<<13)|((66<<0)&0X7F);
    CCM->CACRR=0;//设置2分频为1，；1分频则等于0
    CCM->CCSR &= ~(1<<2);//设置pll1_sw_clk=pll1_main_clk=1056MHZ


    //!!若设置成超频，就改变DIV的值 */


    //**设置PLL2的4路PFD */
    reg=0;
    reg= CCM_ANALOG->PFD_528;
    reg &= ~(0x3F3F3F3F);
    reg |= (32<<24);                     //**PLL2_PDF3=297MHZ */
    reg |= (24<<16);                    //**PLL2_PDF2=396MHZ */
    reg |= (16<<8);                    //**PLL2_PDF1=594MHZ */
    reg |= (27<<0);                   //**PLL2_PDF0=352MHZ */,(528*18)/352=27
    CCM_ANALOG->PFD_528=reg;

     //**设置PLL3的4路PFD */
    reg=0;
    reg= CCM_ANALOG->PFD_528;
    reg &= ~(0x3F3F3F3F);
    reg |= (19<<24);                     //**PLL3_PDF3=454.7MHZ */
    reg |= (17<<16);                    //**PLL3_PDF2=508.2MHZ */
    reg |= (16<<8);                    //**PLL3_PDF1=540MHZ */
    reg |= (12<<0);                   //**PLL3_PDF0=720MHZ */
    CCM_ANALOG->PFD_480=reg;


//**设置AHB_CLK_ROOT=132MHZ */
    CCM->CBCMR &= ~(3 << 18); 	/* 清除设置*/ 
	CCM->CBCMR |= (1 << 18);	/* pre_periph_clk=PLL2_PFD2=396MHz */
	CCM->CBCDR &= ~(1 << 25);	/* periph_clk=pre_periph_clk=396MHz */
	while(CCM->CDHIPR & (1 << 5));/* 等待握手完成 */
		
	/* 修改AHB_PODF位的时候需要先禁止AHB_CLK_ROOT的输出，但是
	 * 我没有找到关闭AHB_CLK_ROOT输出的的寄存器，所以就没法设置。
	 * 下面设置AHB_PODF的代码仅供学习参考不能直接拿来使用！！
	 * 内部boot rom将AHB_PODF设置为了3分频，即使我们不设置AHB_PODF，
	 * AHB_ROOT_CLK也依旧等于396/3=132Mhz。
	 */
#if 0
	/* 要先关闭AHB_ROOT_CLK输出，否则时钟设置会出错 */
	CCM->CBCDR &= ~(7 << 10);	/* CBCDR的AHB_PODF清零 */
	CCM->CBCDR |= 2 << 10;		/* AHB_PODF 3分频，AHB_CLK_ROOT=132MHz */
	while(CCM->CDHIPR & (1 << 1));/  //*等待握手信号
* 等待握手完成 */
#endif
	
	/* 5、设置IPG_CLK_ROOT最小3Mhz，最大66Mhz (boot rom自动设置好了可以不用设置)*/
	CCM->CBCDR &= ~(3 << 8);	/* CBCDR的IPG_PODF清零 */
	CCM->CBCDR |= (1 << 8);		/* IPG_PODF 2分频，IPG_CLK_ROOT=66MHz */
	
	/* 6、设置PERCLK_CLK_ROOT时钟 */
	CCM->CSCMR1 &= ~(1 << 6);	/* PERCLK_CLK_ROOT时钟源为IPG_CLK=66mhz */
	CCM->CSCMR1 &= ~(0X3f << 0);	/* PERCLK_PODF位清零，即1分频,PERCLK_CLK_ROOT=66mhz */

}
