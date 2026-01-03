#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int fd;
    int ret;

    fd=open("./test.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    //ret = truncate("./test.txt", 1024);//截断文件
    ret=ftruncate(fd, 4096);
    if (ret == -1) {
        perror("truncate");
        return 1;
    }

    close(fd);
    return 0;
}