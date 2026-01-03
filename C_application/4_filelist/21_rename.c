#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ret;
    //ret = rename("file1.txt", "file2.txt");//重命名
    ret = rename("./file1.txt", "../file2.txt");//移动到上一级
    if (ret == -1)
    {
        perror("rename");
        exit(EXIT_FAILURE);
    }
    return 0;
}