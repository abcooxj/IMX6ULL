#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static char buf[4096];

int main(void)
{
    int fd;

    fd = open("./tesd.txt", O_WRONLY | O_CREAT|O_EXCL, 0666);//若加入O_DSYNC，则下面的函数不需要sync同步数据
    if (fd == -1) {
        perror("open");
        return 1;
    }

    for(int i=0; i<4096; i++) {//写入大小为4096*4k=16M
        write(fd, buf, sizeof(buf));
    }

    //fsync(fd); 
    //fdatasync(fd); //这两个函数作用一样，都是将文件描述符fd对应的文件内容同步到磁盘上
    sync(fd);
    close(fd);

    return 0;
}