#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int ret,sd,ch;
    char hostname[30];
    struct utsname info = {0};
    struct sysinfo info1 = {0};

    ret = uname(&info);
    sd = sysinfo(&info1);
    if (-1 == ret)
    {
        perror("uname error");
        return 1;
    }

    memset(hostname, 0x0, sizeof(hostname));
    ch = gethostname(hostname, sizeof(hostname));
    if (-1 == ch)
    {
        perror("gethostname error");
    }

    printf("操作系统名称: %s\n", info.sysname);
    printf("主机名: %s\n", info.nodename);
    printf("内核版本: %s\n", info.release);
    printf("系统版本: %s\n", info.version);
    printf("硬件架构: %s\n", info.machine);

    printf("uptime: %ld\n", info1.uptime);
    printf("totalram: %lu\n", info1.totalram);
    printf("freeram: %lu\n", info1.freeram);
    printf("procs: %u\n", info1.procs);

    puts(hostname);

    printf("每个用户最大并发进程数: %ld\n", sysconf(_SC_CHILD_MAX));
    printf("系统节拍率: %ld\n", sysconf(_SC_CLK_TCK));
    printf("页大小: %ld\n", sysconf(_SC_PAGESIZE));

    return 0;
}
