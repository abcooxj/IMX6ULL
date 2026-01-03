#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    FILE *f = NULL;
    int ret;
    char buf[128] = {0};

    f = fopen("./test.txt", "w+");
    if (f == NULL)
    {
        perror("open file error\n");
        return 1;
    }

    ret = fwrite("hello world", 1, 11, f);
    if (ret < 11)
    {
        printf("write file error\n");
        fclose(f);
        return 1;
    }

    ret = fseek(f, 0, SEEK_SET);
    if (ret == -1)
    {
        perror("fseek error\n");
        fclose(f);
        return 1;
    }

    ret = fread(buf, 1, 11, f);
    if (ret < 11)
    {
        if(ferror(f))
        {
            perror("read file error\n");
            fclose(f);
            return 1;
        }
        else{
            if(feof(f))
            {
                printf("read file end\n");
                fclose(f);
                return 1;
            }
        }
        clearerr(f);
    }

    printf("buf=%s\n", buf);
    fclose(f);
    return 0;
}