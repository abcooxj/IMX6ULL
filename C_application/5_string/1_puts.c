#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str = "Hello World!";
    puts(str);
    puts("Hello World!!!!");//可以自动换行
    printf("Hello!!!!\n");//需要手动换行
    putchar('a');
    putchar('D');
    putchar('\n');//putchar('\n')可以换行
    fputc('a', stdout);//输出到标准输出设备
    fputs("Hello World!\n", stdout);//输出到标准输出设备
    return 0;
    return 0;
}