#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int ret;
    ret=link("./test.txt","test1.txt");
    if(ret==-1)
    {
        perror("link");
        exit(1);
    }

    return 0;
}