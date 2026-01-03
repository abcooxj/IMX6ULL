#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
#if 0
    struct tms t_buf_start;
    struct tms t_buf_end;
    clock_t t_start;
    clock_t t_end;
    long tck;
    int i, j;

    /* 获取系统的节拍率 */
    tck = sysconf(_SC_CLK_TCK);

    /* 开始时间 */
    t_start = times(&t_buf_start);
    if (-1 == t_start)
    {
        perror("times error");
        return 1;
    }
    /* **********需要进行测试的代码段********** */
    for (i = 0; i < 20000; i++)
        for (j = 0; j < 20000; j++)
            ;
    sleep(1); // 休眠挂起
    /* ***************************end********************* */

    /* ***结束时间*** */
    t_end = times(&t_buf_end);
    if (-1 == t_end)
    {
        perror("times error");
        return 1;
    }
    /*打印时间*/
    printf("时间总和：%f秒\n",(t_end-t_start) / (double)tck);
    printf("系统CPU时间:%.2f 秒\n", (t_buf_end.tms_utime - t_buf_start.tms_utime) / (double)tck);
    printf("用户CPU时间:%.2f 秒\n", (t_buf_end.tms_stime - t_buf_start.tms_stime) / (double)tck);

    return 0;
#endif

        clock_t t_start;
        clock_t t_end;
        int i, j;

        /* 开始时间 */
        t_start = clock();
        if (-1 == t_start)
            exit(-1);

        /********** 需要进行测试的代码段 **********/
        for (i = 0; i < 20000; i++)
            for (j = 0; j < 20000; j++)
                ;
        /********** end **********/

        /* 结束时间 */
        t_end = clock();
        if (-1 == t_end)
            return 1;

        /* 打印总CPU时间 */
        printf("总的CPU时间: %f\n", (double)(t_end - t_start) / CLOCKS_PER_SEC);
      

        return 0;
    
}