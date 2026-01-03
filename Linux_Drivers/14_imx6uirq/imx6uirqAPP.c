#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

/*
 *argc:应用程序参数个数
 *argv[]:具体的参数内容，字符串形式 
 *./timerAPP  <filename>  <0:1> 0表示关灯，1表示开灯
 * ./timerAPP /dev/timer 0    关灯
 * ./timerAPP /dev/timer 1    开灯
 */

int main(int argc, char *argv[])
{
    
    int fd, ret;
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

    //**循环读取 */
    while(1)
    {
        ret = read(fd, &data, sizeof(data));
        if(ret < 0) 
        {

        } else 
        {
            if(data)
                printf("key value = %#x\r\n", data);
        }
    }

    close(fd);

    return 0;
}
