#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    char buf[128]={0};
    getcwd(buf,sizeof(buf));
    printf("current dir is %s\n",buf);

    chdir("../");
    getcwd(buf,sizeof(buf));
    printf("current dir is %s\n",buf);

    return 0;
}