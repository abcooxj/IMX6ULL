#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#define LEDOFF 	0
#define LEDON 	1

/*
 * @description		: main主程序
 * @param - argc 	: argv数组元素个数
 * @param - argv 	: 具体参数
 * @return 			: 0 成功;其他 失败
 */
int main(int argc, char *argv[])
{
	int fd, retvalue;
	char *filename;
	unsigned char databuf[4];
	
	if(argc != 2){
		printf("Error Usage!\r\n");
		return -1;
	}

	filename = argv[1];

	/* 打开驱动 */
	fd = open(filename, O_RDWR);
	if(fd < 0){
		printf("file %s open failed!\r\n", argv[1]);
		return -1;
	}

	//databuf[0] = atoi(argv[2]);	/* 要执行的操作：打开或关闭 */

	while (1)
	{
		if (read(fd, databuf, 4) == 4)
		{
			printf("get humidity  : %d.%d\n", databuf[0], databuf[1]);
			printf("get temprature: %d.%d\n", databuf[2], databuf[3]);
		}
		else 
		{
			printf("get humidity/temprature: -1\n");
		}
		sleep(5);
	}

	return 0;
}
