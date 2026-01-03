#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    FILE *file=NULL;
    int ret;
    int fd;

    file = fopen("./tesr.txt", "w");
    if(file == NULL)
    {
        perror("fopen");
        exit(1);
    }

    fd=fileno(file);
    if(fd == -1)
    {
        perror("fileno");
        exit(1);
    }

    ret=write(fd, "hello world11", 13);
    if(ret == -1)
    {
        perror("write");
        fclose(file);
        exit(1);

    }
    fclose(file);
    return 0;
}