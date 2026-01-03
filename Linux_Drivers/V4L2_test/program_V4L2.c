#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <string.h>

//打开摄像头/dev/video
int main(int argc, char *argv[])/*参数个数，参数设备路径/dev/video*/
{
    int fd;
    
    struct v4l2_fmtdesc fmtdesc;
    int fmt_index = 0;
    int frame_index = 0;
    struct v4l2_frmsizeenum fsenum;
    if(argc !=2)
    {
        printf("Usage: %s <dev>\n", argv[0]);
        return -1;
    }

    //open
    fd=open(argv[1], O_RDWR);
    if(fd < 0)
    {
        printf("can't open %s\n", argv[1]);
        return -1;
    }

    while(1)//循环枚举格式
    {
        /*枚举格式*/
        fmtdesc.index = fmt_index;//从0开始
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; //type视频捕获
        if(0 !=ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc))//枚举格式
        {
            printf("VIDIOC_ENUM_FMT failed\n");
            break;
        }

        frame_index = 0;//当前格式的每种帧大小枚举
        while(1)//循环枚举帧大小
        {
            //枚举这种格式支持的帧大小
            memset(&fsenum, 0, sizeof(struct v4l2_frmsizeenum));
            fsenum.pixel_format = fmtdesc.pixelformat; // pixel_format: 使用当前格式的像素格式
            fsenum.index = frame_index;//当前的索引

            if (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &fsenum) == 0) // 当前格式支持的帧大小
            {
                printf("format %s,%d, framesize %d: %d x %d\n", fmtdesc.description, 
                    fmtdesc.pixelformat,
                     frame_index, 
                     fsenum.discrete.width, 
                     fsenum.discrete.height);
            }
            else
            {
                break;
            }
            frame_index++;
        }
        fmt_index++;
    }
}