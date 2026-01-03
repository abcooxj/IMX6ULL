#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    struct stat st;
    int ret;

    ret=stat("./test.txt",&st);//回去文件属性，把属性放到st中
    if(ret==-1)
    {
        perror("stat");
        exit(1);
    }

    printf("inode: %ld\n",st.st_ino);
    printf("size: %ld\n",st.st_size);
    printf("type: ");

    if(S_ISREG(st.st_mode))
    {
        printf(" 普通文件");
    }
    else if(S_ISDIR(st.st_mode))
    {
        printf(" 目录");
    }
    else if (S_ISCHR(st.st_mode))
    {
        printf("字符设备 ");
    }
    else if (S_ISBLK(st.st_mode))
    {
        printf(" 块设备");
    }
    else if (S_ISFIFO(st.st_mode))
    {
        printf("管道 ");
    }
    else if (S_ISLNK(st.st_mode))
    {
        printf(" 链接");
    }
    else if (S_ISSOCK(st.st_mode))
    {
        printf("套接字 ");
    }

    printf("\n");
    return 0;
}