#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
    int ret;

    ret = mkdir("./testdir", 0666);
    if (ret == -1) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    return 0;
}