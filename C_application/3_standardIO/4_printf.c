#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    //FILE *f=NULL;
    char buf[128]={0};

    //f=fopen("./test.txt","w+");
    //if(f==NULL)
    //{
    //    perror("fopen");
    //    return 1;
    //}
    //fprintf(f,"hello world  %d\n",100);
    //fprintf(stdout,"hello world  %d\n",100);

    //dprintf(1, "hello world  %d\n", 100);//标准输出
    //dprintf(2, "hello world  %d\n", 100);//标准错误

    //sprintf(buf,"hello world  %d\n",200);
    snprintf(buf, 128,"hello world  %d\n", 200);
    printf("%s",buf);

    return 0;
}