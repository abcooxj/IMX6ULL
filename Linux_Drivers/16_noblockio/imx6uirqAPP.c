#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>

/*
 *argc:应用程序参数个数
 *argv[]:具体的参数内容，字符串形式 
 *./timerAPP  <filename>  <0:1> 0表示关灯，1表示开灯
 * ./timerAPP /dev/timer 0    关灯
 * ./timerAPP /dev/timer 1    开灯
 */

int main(int argc, char *argv[])
{
   // fd_set readfds;
    struct pollfd fds;
    //struct timeval timeout;
    int fd, ret;
    char *filename;
    unsigned char data;
  

    if(argc != 2) {
        printf("Error Usage!\r\n");
        return -1;
    }

    filename = argv[1];

    fd = open(filename, O_RDWR|O_NONBLOCK);//***非阻塞打开 */
    if(fd < 0) {
        printf("file %s open failed!\r\n", filename);
        return -1;
    }
#if 0
    //**循环读取 */
    while(1)
    {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        //timeout.tv_sec = 0;
        //timeout.tv_usec = 50000000;//**500ms */

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        ret = select(fd+1, &readfds, NULL, NULL, &timeout);
        switch(ret)
        {
            case 0://**超时 */
                printf("time out!\r\n");
                break;
            case -1://**错误 */
                break;
            default://**有数据 */
                if(FD_ISSET(fd, &readfds))
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
        }

        
    }
#endif

    //**循环读取 */
    while(1)
    {
        fds.fd = fd;
        fds.events = POLLIN;
        ret = poll(&fds, 1, 500);//**超时500ms */
        if(ret==0)//**超时 */
        {
            //printf("time out!\r\n");
        }
        else if(ret<0)//**错误 */
        {
            //printf("error!\r\n");
        }
        else//**有数据 */
        {
            if(fds.revents & POLLIN)//**可读取 */
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
        }
        
    }

    close(fd);

    return 0;
}
