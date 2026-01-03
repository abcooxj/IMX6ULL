#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int ret;

    ret=chown("./test.txt",0,0);
    if(ret==-1)
    {
        perror("chown");
        exit(1);
    }

    return 0;
}