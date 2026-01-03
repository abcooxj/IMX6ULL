#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd1,fd2;
    int ret;
    char buf[128]={0};

    fd1=open("./test.txt",O_RDWR|O_TRUNC);
    if(fd1== -1){
        perror("open1");
        return 1;
    }

    fd2 = dup2(fd1,1000);
    //fd2=dup(fd1);
    if(fd2==-1){
        perror("dup");
        close(fd1);
        return 1;
    }
    printf("fd1=%d,fd2=%d\n",fd1,fd2);

    ret=write(fd2,"hello world",12);
    if(ret==-1){
        perror("write");
        close(fd1);
        close(fd2);
        return 1;
    }

    lseek(fd1, 0, SEEK_SET);//在没有使用lseek的情况下，read会从文件开头开始读，所以需要将文件指针移动到文件开头，所以读不到数据

    read(fd1,buf,12);
    if(ret==-1){
        perror("read");
        close(fd1);
        close(fd2);
        return 1;
    }

    printf("read: %s\n",buf);

    close(fd1);
    close(fd2);
    return 0;
}