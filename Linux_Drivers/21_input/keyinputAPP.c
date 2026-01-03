#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/input.h>


/*
 *argc:应用程序参数个数
 *argv[]:具体的参数内容，字符串形式 
 *./timerAPP  <filename>  <0:1> 0表示关灯，1表示开灯
 * ./timerAPP /dev/timer 0    关灯
 * ./timerAPP /dev/timer 1    开灯
 */

 static struct input_event inputevent;


int main(int argc, char *argv[])
{
    
    int fd, err;
    char *filename;
    unsigned char data;
  

    if(argc != 2) {
        printf("Error Usage!\r\n");
        return -1;
    }

    filename = argv[1];

    fd = open(filename, O_RDWR);
    if(fd < 0) {
        printf("file %s open failed!\r\n", filename);
        return -1;
    }

    while(1) {
        err = read(fd, &inputevent, sizeof(inputevent));
        if(err > 0) { /* 数据读取成功 */
           switch(inputevent.type) {
                case EV_KEY:
                    if(inputevent.code < BTN_MISC) { /* KEY */
                        printf("key %d %s\r\n", inputevent.code, inputevent.value?"press":"release");
                    } else {                        /* BTN */
                        printf("button %d %s\r\n", inputevent.code, inputevent.value?"press":"release");
                    }
                    break;
                case EV_SYN:
                    break;
                case EV_REL:
                    break;
                case EV_ABS:
                    break;
           } 
        } else {
            printf("读取数据失败\r\n");
        }
    }

    

    close(fd);

    return 0;
}
