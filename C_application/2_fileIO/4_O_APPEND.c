#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// 先存入 echo "abcksdfh" >test.txt，执行文件后会显示abcksdfh hello

    int
    main(void)
{
    int fd;
    int ret;

    fd = open("./test.txt", O_WRONLY | O_APPEND); //若没有加 O_APPEND，只会显示hello
    if (fd == -1) 
    {
        perror("open");
        return 1;
    }

    ret = write(fd, "hello\n", 6);
    if (ret == -1)
    {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}