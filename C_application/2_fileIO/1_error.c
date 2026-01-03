#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    int fd;
    printf("error=%d\n",errno);

    fd = open("./tesd.txt",O_RDONLY);//文件若存在，则不能返回错误
    if(fd == -1)
    {
        printf("aab");
        printf("errno=%d\n",errno);
        //printf("error=%s\n",strerror(errno));
        perror("");
        perror("open error");
        return 1;
    }
    return 0;
}