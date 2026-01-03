#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MY_FILE "test.txt"

int main(void)
{
    int ret;

    //检查文件是否存在
    ret= access(MY_FILE,F_OK);
    if(ret == -1)
    {
        printf("File %s exists\n",MY_FILE);
        return 1;

    }

    //检查文件权限
    ret= access(MY_FILE,R_OK);
    if(!ret)
    {
        printf("readable\n");
    }
    else
    {
        printf("not readable\n");
    }
    ret=access(MY_FILE,W_OK);
    if(!ret)
    {
        printf("writable\n");
    }
    else
    {
        printf("not writable\n");
    }
    ret = access(MY_FILE, X_OK);
    if (!ret)
    {
        printf("execution\n");
    }
    else
    {
        printf("not execution\n");
    }

    return 0;
}