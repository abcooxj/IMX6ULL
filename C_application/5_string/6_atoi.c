#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    printf("atoi: %d\n", atoi("500"));
    printf("atol: %ld\n", atol("500"));
    printf("atoll: %lld\n", atoll("500"));

    printf("strtol: %ld\n", strtol("0x500", NULL, 16));
    printf("strtol: %ld\n", strtol("0x500", NULL, 0));
    printf("strtol: %ld\n", strtol("500", NULL, 16));
    printf("strtol: %ld\n", strtol("0777", NULL, 8));
    printf("strtol: %ld\n", strtol("0777", NULL, 0));
    printf("strtol: %ld\n", strtol("1111", NULL, 2));
    printf("strtol: %ld\n", strtol("-1111", NULL, 2));

    printf("strtoul: %lu\n", strtoul("0x500", NULL, 16));
    printf("strtoul: %lu\n", strtoul("0x500", NULL, 0));
    printf("strtoul: %lu\n", strtoul("500", NULL, 16));
    printf("strtoul: %lu\n", strtoul("0777", NULL, 8));
    printf("strtoul: %lu\n", strtoul("0777", NULL, 0));
    printf("strtoul: %lu\n", strtoul("1111", NULL, 2));

    exit(0);
}