#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    //if(setvbuf(stdout, NULL, _IONBF, 0))//无缓冲
    //{
    //    perror("setvbuf");
    //    exit(1);
    //}
    printf("Hello, world!\n");//行缓冲
    printf("Hello, world!2222");

    fclose(stdout);//关闭文件描述符,关闭文件会刷新缓冲区
    fflush(stdout);//强制刷新缓冲区

    while(1)
    {
        sleep(1);
    }
 
    return 0;
    //程序退出时，会刷新缓冲区
}