#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int ret;

    ret = unlink("./test.txt");
    if (ret == -1)
    {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}