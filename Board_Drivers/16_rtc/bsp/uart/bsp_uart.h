#ifndef  __BSP_UART_H
#define  __BSP_UART_H
#include "imx6u.h"

void uart_init(void);
void uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz);
void uart_disable(UART_Type *base);
void uart_enable(UART_Type *base);
void uart_softreset(UART_Type *base);
void putc(unsigned char c);
void puts(char *str);
unsigned char getc(void);
void raise(int sig_nr);
void uart_io_init(void);
#endif  
