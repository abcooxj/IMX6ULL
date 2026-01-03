#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <utime.h>
#include <time.h>

int main(void)
{
    int ret;
    struct utimbuf times={0};
    time_t cur_sec;

    //获取当前时间
    time(&cur_sec);
    times.actime = cur_sec;
    times.modtime = cur_sec;

    ret = utime("test.txt", &times);
    if( ret == -1)
    {
        perror("utime");
        exit(EXIT_FAILURE);
    }
   

    return 0;
}