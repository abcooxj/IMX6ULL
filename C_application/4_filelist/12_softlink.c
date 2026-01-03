#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int ret;

    ret=symlink("./test.cc","./soft.txt");//悬空连接
    if(ret==-1)
    {
        perror("symlink error");
        exit(1);
    }

    return 0;
}