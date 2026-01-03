#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int ret;
    ret = chmod("test.txt", 0777);
    if (ret == -1) {
        perror("chmod");
        return 1;
    }

    return 0;
}