#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char buf[125]={0};
    //memset(buf,0x0,sizeof(buf));//将buf设置为0，清空数组
    int ret;

    fd=open("./test.txt",O_RDONLY);
    if(fd==-1)
    {
        printf("open ERROR\n");
        return 1;
    }

    printf("open success\n");
    ret=read(fd,buf,11);
    if(ret==-1)
    {
        printf("read ERROR\n");
        close(fd);
        return 1;
    }
    printf("read %d bytes %s success\n",ret,buf);
    
    close(fd);
    return 0;
}