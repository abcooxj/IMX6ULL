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

    fd = open("./test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    ret=fcntl(fd, F_GETFL);
    if (ret == -1) {
        perror("fcntl");
        return 1;
    }

    printf("flags: 0x%x\n", ret);

    ret=fcntl(fd, F_SETFL, ret | O_APPEND);
    if (ret == -1) {
        perror("fcntl setfl");
        return 1;
    }

    ret=fcntl(fd, F_GETFL);
    if (ret == -1) {
        perror("fcntl getfl");
        return 1;
    }

    printf("flags: 0x%x\n", ret);

    close(fd);
    return 0;
}