#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <utime.h>
#include <time.h>
#include <sys/time.h>

int main(void)
{
    int ret;
    struct timeval timeal_arr[2];
    time_t cur_sec;

    // 获取当前时间
    time(&cur_sec);
    for(int i=0; i<2; i++)
    {
        timeal_arr[i].tv_sec = cur_sec;
        timeal_arr[i].tv_usec = 0;
    }

    ret = utimes("test.txt", timeal_arr);
    if (ret == -1)
    {
        perror("utimes");
        exit(EXIT_FAILURE);
    }

    return 0;
}