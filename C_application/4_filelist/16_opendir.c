#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>

int main(void)
{
    DIR *dir=NULL;
    struct dirent *rent;
    int ret;

    dir = opendir("./");
    if(dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while((rent = readdir(dir)))
    {
        printf("%s: %ld\n", rent->d_name,rent->d_ino);

    }
    if(rent == NULL)
    {
       if(errno == !0)
       {
           perror("readdir");
       }
       else
       {
           printf("read end\n");
       }
    }
   closedir(dir); 
   return 0;
}