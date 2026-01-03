#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    char buf[128];

    getcwd(buf, sizeof(buf));
    printf("Current working directory: %s\n", buf);

    return 0;
}