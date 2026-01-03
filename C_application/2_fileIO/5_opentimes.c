#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd1;
    int fd2;

    fd1 = open("./test.txt", O_WRONLY|O_TRUNC|O_APPEND);
    if(fd1 == -1)
    {
        perror("open1");
        return 1;
    }

    fd2 = open("./test.txt", O_WRONLY|O_APPEND);
    if(fd2 == -1)
    {
        perror("open2");
        close(fd1);
        return 1;
    }

    write(fd1, "hello", 5);
    write(fd2, "world", 5);

    close(fd1);
    close(fd2);
    return 0;
}