#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd;
    fd=open("./test.txt",O_RDONLY|O_TRUNC);
    if(fd==-1)
    {
        perror("open ERROR");
        return 1;
    }
    close(fd);
    return 0;
}