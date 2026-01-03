#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *str = "World!";
    char buf[128] = {'H', 'e', 'l', 'l', 'o', '!'};
    char sd[128]={0};

    strcat(buf, str);
    puts(buf);

    strcpy(sd, "sjedfosi");
    puts(sd);

    memset(buf,0x0,sizeof(buf));//buf清零

    return 0;
}
