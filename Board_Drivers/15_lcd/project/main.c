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
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"

/* 背景颜色索引 */
unsigned int backcolor[10] = {
	LCD_BLUE, 		LCD_GREEN, 		LCD_RED, 	LCD_CYAN, 	LCD_YELLOW, 
	LCD_LIGHTBLUE, 	LCD_DARKBLUE, 	LCD_WHITE, 	LCD_BLACK, 	LCD_ORANGE

}; 
	

//*跳转到C语言main函数 */
int main(void)
{
	static unsigned char state=0;
	//unsigned int color=0;
	unsigned char index=0;

	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();  //*初始化延时
	uart_init();  //*初始化串口
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	key_init();   //*初始化按键过滤
	lcd_init();   //*初始化屏幕
	

	//lcd_drawpoint(0,0,LCD_RED);//** 左上方*/
	//lcd_drawpoint(tftlcd_dev.width-1,0,LCD_RED);//**右上方 */
	//lcd_drawpoint(0,tftlcd_dev.height-1,LCD_RED);//**左下方 */
	//lcd_drawpoint(tftlcd_dev.width-1,tftlcd_dev.height-1,LCD_RED);//**右下方 */

	//color=lcd_readpoint(0,0);
	//printf("左上方=%#x\r\n",color);

	//color=lcd_readpoint(tftlcd_dev.width-1,0);
	//printf("右上方=%#x\r\n",color);

	//color=lcd_readpoint(0,tftlcd_dev.height-1);
	//printf("左下方=%#x\r\n",color);

	//color=lcd_readpoint(tftlcd_dev.width-1,tftlcd_dev.height-1);
	//printf("右下方=%#x\r\n",color);


	//lcd_fill(0,0,100,100,LCD_RED);

	tftlcd_dev.forecolor=LCD_RED;
	tftlcd_dev.backcolor=LCD_WHITE;
	lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPHA IMX6U"); 	
	lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
	lcd_show_string(10, 110, 240, 16, 16,(char*)"ATOM@ALIENTEK");      					 
	lcd_show_string(10, 130, 240, 12, 12,(char*)"2025/1/6");	      		
	while(1)			
	{	
		index++;
		lcd_clear(backcolor[index]);
		lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPHA IMX6U"); 	
		lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
		lcd_show_string(10, 110, 240, 16, 16,(char*)"ATOM@ALIENTEK");      					 
		lcd_show_string(10, 130, 240, 12, 12,(char*)"2025/1/6");	   

		if(index==10)
		{
			index=0;
		}
		state = !state;
		led_switch(LED0,state);
		delay_ms(1000);
	}

	return 0;
}
