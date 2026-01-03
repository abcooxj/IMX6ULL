#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char buf[4096];

int main(void)
{
    int fd;
    int ret;

    fd=open("./test.txt", O_CREAT|O_WRONLY|O_EXCL, 0644);
    if(fd==-1)
    {
        perror("open error\n");
        return 1;
    }
      ret=lseek(fd,4096,SEEK_SET);
      if(ret==-1)
      {
          perror("lseek error\n");
          close(fd);
          return 1;
      }  

     ret= write(fd, buf,4096);
     if(ret==-1)
     {
         perror("write error\n");
         close(fd);
         return 1;
     }

     printf("write %d bytes\n",ret);
     close(fd);
     return 0;
}