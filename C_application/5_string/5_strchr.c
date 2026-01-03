#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char *ptr = NULL;
    char str[] = "Hello World! W";

    ptr = strstr(str, "World");
    //ptr = strrchr(str, 'W');
    //ptr = strchr(str, 'W');
    if (NULL != ptr)
    {
        printf("Character: %s\n", ptr);
        printf("Offset: %ld\n", ptr - str);
    }
    exit(0);
}