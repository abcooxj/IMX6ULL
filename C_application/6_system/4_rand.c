#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
#if 0
    int ret;
    for (int i = 0; i < 10; i++)
    {
        ret = rand();
        printf("%d ", ret);
    }
    printf("\n");
    return 0;
#endif

    int random_number_arr[8];
    int count;

    /* 设置随机数种子 */
    srand(time(NULL));

    /* 生成伪随机数组 */
    for (count = 0; count < 8; count++)
        random_number_arr[count] = rand() % 100;

    /* 打印随机数组 */
    printf("[");
    for (count = 0; count < 8; count++)
    {
        printf("%d", random_number_arr[count]);
        if (count != 8 - 1)
            printf(" , ");
    }
    printf("]\n");

    return 0;
}
