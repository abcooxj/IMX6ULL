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


int main(int argc, char *argv[])
{
    
    int fd, err;
    char *filename;
    unsigned short  data[3];
    unsigned short ir, ps, als;
  

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
        err = read(fd, data, sizeof(data));
        if(err == 0) {
            ir = data[0];
            als = data[1];
            ps = data[2];
            printf("AP3216C ir = %d, als = %d, ps = %d\r\n", ir, als, ps);
        }
        usleep(200000);  /* 200ms */
    }
    


    close(fd);

    return 0;
}
