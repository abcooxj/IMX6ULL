#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int fd;
    FILE *file=NULL;
    int ret;

    fd = open("tesw.txt", O_WRONLY | O_CREAT|O_TRUNC, 0666);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    file = fdopen(fd, "w");
    if(file == NULL)
    {
        perror("fdopen");
        close(fd);
        exit(1);
    }

    fwrite("hello world",1,11,file);
    if(ret < 11)
    {
        perror("fwrite");
        fclose(file);
        exit(1);
    }
    fclose(file);
    return 0;
}