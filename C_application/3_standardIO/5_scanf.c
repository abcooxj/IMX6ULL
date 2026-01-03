#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    //char buf[128]={0};

    //scanf("%s", buf);
    //fscanf(stdin,"%s", buf);
    //printf("%s\n",buf);


    int data;
    char buf1[128];
    char buf2[128];
    sscanf("100 hello  woeld","%d  %s  %s",&data,buf1,buf2);
   printf("%d\n",data);
    printf("%s\n",buf1);
    printf("%s\n",buf2);
    return 0;
}