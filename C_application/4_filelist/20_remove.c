#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ret;

    ret=remove("./soft.txt");
    if(ret==-1)
    {
        printf("删除shibai\n");
        return 1;
    }
    return 0;
}