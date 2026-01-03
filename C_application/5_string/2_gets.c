#include <stdio.h>

int main(void)
{
   //char buf[128]={0};
   
   //gets(buf);//一般不使用这个程序，不稳定
   //puts(buf);

   char s1[100]={0};
   char s2[100]={0};

   scanf("%s",s1);
   printf("s1=%s\n",s1);

   scanf("%s",s2);
   printf("s2=%s\n",s2);//空格作为分隔符

   return 0;
}