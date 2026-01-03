#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define _GNU_SOURCE

static char buf[4096];

int main(void)
{
   int fd;
   int ret;
   
   fd=open("./tesc.txt", O_WRONLY|O_CREAT|O_EXCL|O_DIRECT,0666);
   if(fd==-1)
   {
      perror("open");
      return 1;
   }

   lseek(fd,4096,SEEK_SET);

   for(int i=0;i<4096;i++)
   {
      ret=write(fd,buf,sizeof(buf));
      if(ret==-1)
      {
         perror("write");
         close(fd);
         return 1;
      }
   }
   close(fd);
   return 0;
}