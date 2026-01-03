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
    struct timespec tmsp_arr[2];
    int ret;
    int fd;

    //打开文件
    fd = open("./test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* 修改文件时间戳 */
#if 1
    ret = futimens(fd, NULL); // 同时设置为当前时间
#endif
#if 0
    tmsp_arr[0].tv_nsec = UTIME_OMIT;//访问时间保持不变
    tmsp_arr[1].tv_nsec = UTIME_NOW;//内容修改时间设置为当期时间
    ret = futimens(fd, tmsp_arr);
#endif

#if 0
    tmsp_arr[0].tv_nsec = UTIME_NOW;//访问时间设置为当前时间
    tmsp_arr[1].tv_nsec = UTIME_OMIT;//内容修改时间保持不变
    ret = futimens(fd, tmsp_arr);
#endif
    if (-1 == ret)
    {
        perror("futimens error");
       return 1;
    }

    close(fd);
    return 0;
}