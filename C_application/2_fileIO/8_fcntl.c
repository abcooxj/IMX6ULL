#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int fd1,fd2;
    int ret;

    fd1=open("./test.txt",O_RDONLY);
    if(fd1==-1)
    {
        perror("open");
        return 1;
    }

    fd2=fcntl(fd1,F_DUPFD,0);
    if(fd2==-1)
    {
        perror("fcntl");
        return 1;
    }

    printf("fd1=%d,fd2=%d\n", fd1, fd2); // fd1=3,fd2=4;    0,1,2是标准输入输出错误,只能从3开始

    close(fd1);
    close(fd2);
    return 0;
}