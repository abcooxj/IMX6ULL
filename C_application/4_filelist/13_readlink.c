#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int ret;
    char buf[128]={0};

    ret = readlink("./soft.txt", buf, sizeof(buf));
    if (ret == -1)
    {
        perror("readlink error");
        exit(1);
    }

    printf("ret = %d\n", ret);
    printf("buf = %s\n", buf);

    return 0;
}