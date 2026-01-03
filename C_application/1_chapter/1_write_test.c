#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int fd;
    int ret;

    fd=open("./test.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);//0644表示文件权限,表示其他用户和同组用户只读，所属用户可读可写
    if(fd==-1)
    {
        printf("file error exist\n");
        return 1;
    }
     
    printf("open ok\n");

    ret=write(fd, "hello world", 11);
    if(ret==-1)
    {
        printf("write error\n");
        close(fd);
        return 1;
    }

   printf("write ok  %d bytes\n",ret);

   close(fd);
    return 0;
}