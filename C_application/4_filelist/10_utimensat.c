#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <utime.h>
#include <time.h>
#include <sys/time.h>

#define MY_FILE "test.txt"

int main(void)
{
    struct timespec tmsp_arr[2];
    int ret;
    int fd;

    /* 检查文件是否存在 */
    ret = access(MY_FILE, F_OK);
    if (-1 == ret)
    {
        printf("Error: %s file does not exist!\n", MY_FILE);
        exit(1);
    }
/* 修改文件时间戳 */
#if 1
    ret = utimensat(AT_FDCWD, MY_FILE, NULL, 0); // 同时设置为当前时间
#endif
#if 0
    tmsp_arr[0].tv_nsec = UTIME_OMIT;//访问时间保持不变
    tmsp_arr[1].tv_nsec = UTIME_NOW;//内容修改时间设置为当期时间
    ret = utimensat(AT_FDCWD, MY_FILE, tmsp_arr, 0);
#endif
#if 0
    tmsp_arr[0].tv_nsec = UTIME_NOW;//访问时间设置为当前时间
    tmsp_arr[1].tv_nsec = UTIME_OMIT;//内容修改时间保持不变
    ret = utimensat(AT_FDCWD, MY_FILE, tmsp_arr, 0);
#endif
    if (-1 == ret)
    {
        perror("futimens error");
        return 1;
    }
    
    return 0;
}