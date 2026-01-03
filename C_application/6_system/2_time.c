#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(void)
{
    time_t t;

    t = time(NULL);
    if (t == -1)
    {
        perror("time error");
        return 1;
    }

    printf("time: %ld\n", t);

    struct timeval tval;
    int ret;

    ret = gettimeofday(&tval, NULL);
    if (-1 == ret)
    {
        perror("gettimeofday error");
        return 1;
    }

    printf("时间值：%ld 秒+ %ld 微秒\n", tval.tv_sec, tval.tv_usec);

#if 1
    char tm_str[100] = {0};
    time_t tm;

    /* 获取当前时间 */
    tm = time(NULL);
    if (-1 == tm)
    {
        perror("time error");
        return 1;
    }

    /* 将时间转换为字符串形式 */
    ctime_r(&tm, tm_str);

    /* 打印输出 */
    printf("当前时间为：%s", tm_str);
 #endif
    
#if 1
    struct tm tt;
    time_t sec;

    /* 获取时间 */
    sec = time(NULL);
    if (-1 == sec) {
        perror("time error");
        return 1;
    }

    /* 转换得到本地时间 */
    localtime_r(&sec, &tt);

    /* 打印输出 */
    printf("当前时间为：%d年%d月%d日 %d:%d:%d\n",
           tt.tm_year + 1900, tt.tm_mon, tt.tm_mday,
           tt.tm_hour, tt.tm_min, tt.tm_sec);
#endif

    struct tm local_t;
    struct tm utc_t;
    //time_t sec;

    /* 获取时间 */
    sec = time(NULL);
    if (-1 == sec)
    {
        perror("time error");
        return 1;
    }
        

    /* 转换得到本地时间 */
    localtime_r(&sec, &local_t);
    /* 转换得到国际标准时间 */
    gmtime_r(&sec, &utc_t);

    //打印输出
    printf("本地时间：%d年%d月%d日 %d:%d:%d\n",
           local_t.tm_year + 1900, local_t.tm_mon, local_t.tm_mday,
           local_t.tm_hour, local_t.tm_min, local_t.tm_sec);
    printf("UTC 时间：%d年%d月%d日 %d:%d:%d\n",
           utc_t.tm_year + 1900, utc_t.tm_mon, utc_t.tm_mday,
           utc_t.tm_hour, utc_t.tm_min, utc_t.tm_sec);

    struct tm local_tt;
    //time_t sec;
    /* 获取时间 */
    sec = time(NULL);
    if (-1 == sec)
    {
        perror("time error");
        exit(-1);
    }
    printf("获取得到的秒数：%ld\n", sec);
    localtime_r(&sec, &local_tt);
    printf("转换得到的秒数：%ld\n", mktime(&local_tt));

    struct tm local_td;
    char tm_strr[100] = {0};
    //time_t sec;

    /* 获取时间 */
    sec = time(NULL);
    if (-1 == sec)
    {
        perror("time error");
        return 1;
    }
        

    localtime_r(&sec, &local_td);
    asctime_r(&local_td, tm_strr);
    printf("本地时间：%s", tm_strr);

    struct tm local_tdd;
    char tm_strdd[100] = {0};
    //time_t sec;

    /* 获取时间 */
    sec = time(NULL);
    if (-1 == sec)
    {
        perror("time error");
        return 1;
    }

    localtime_r(&sec, &local_tdd);
    strftime(tm_strdd, sizeof(tm_strdd), "%Y-%m-%d %H:%M:%S", &local_tdd);
    printf("本地时间：%s\n", tm_strdd);

    return 0;
}
