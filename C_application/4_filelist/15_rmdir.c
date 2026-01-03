#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int ret;

    ret = rmdir("./testde");
    if (ret == -1)
    {
        perror("rmdir");
        return 1;
    }
    return 0;
}