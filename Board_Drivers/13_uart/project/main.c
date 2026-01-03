#include "main.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exit.h"
#include "bsp_epit.h"
#include "bsp_keyfilter.h"
#include "bsp_uart.h"

//*跳转到C语言main函数 */
int main(void)
{
	unsigned char a=0;

	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();  //*初始化延时
	uart_init();  //*初始化串口
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	key_init();   //*初始化按键过滤
	

	while(1)			
	{	
		puts("请输入1个字符:");
		a=getc();
		putc(a); //**回显 */
		puts("\r\n");

		puts("您输入的字符是：");
		putc(a);
		puts("\r\n");
	}

	return 0;
}
