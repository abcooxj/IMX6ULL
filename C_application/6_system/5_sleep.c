#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
#if 0
    puts("Sleep Start!");

    /* 让程序休眠3秒钟 */
    sleep(3);
    //usleep(3*1000*1000);

    puts("Sleep End!");
#endif

    struct timespec request_t;
    puts("Sleep Start!");

    /* 让程序休眠 3 秒钟 */
    request_t.tv_sec = 3;
    request_t.tv_nsec = 0;
    nanosleep(&request_t, NULL);
    puts("Sleep End!");

    return 0;
}
