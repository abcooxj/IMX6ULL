#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <sys/mman.h>
#include <pthread.h>

//通过按键控制摄像头亮度
static void *thread_brightness_control(void *args)
{
    int fd = (int)args;//设备转为文件描述符

    unsigned char c;//按键输入
    int brightness;//当前亮度值
    int delta;//亮度的步长

    struct v4l2_queryctrl qctrl;//参数支持的范围，最大最小
    memset(&qctrl, 0, sizeof(qctrl));
    qctrl.id = V4L2_CID_BRIGHTNESS; // V4L2_CID_BASE+0;
    if (0 != ioctl(fd, VIDIOC_QUERYCTRL, &qctrl))
    {
        printf("can not query brightness\n");
        return NULL;
    }

    printf("brightness min = %d, max = %d\n", qctrl.minimum, qctrl.maximum);
    delta = (qctrl.maximum - qctrl.minimum) / 10;//亮度分为10分

    struct v4l2_control ctl;//控制当前项的值
    ctl.id = V4L2_CID_BRIGHTNESS; // V4L2_CID_BASE+0;
    ioctl(fd, VIDIOC_G_CTRL, &ctl);

    while (1)
    {
        c = getchar();
        if (c == 'u' || c == 'U')
        {
            ctl.value += delta;
        }
        else if (c == 'd' || c == 'D')
        {
            ctl.value -= delta;
        }
        if (ctl.value > qctrl.maximum)//保证在最大值与最小值之间
            ctl.value = qctrl.maximum;
        if (ctl.value < qctrl.minimum)
            ctl.value = qctrl.minimum;

        ioctl(fd, VIDIOC_S_CTRL, &ctl);//设置亮度
    }
    return NULL;
}

// 打开摄像头/dev/video
int main(int argc, char *argv[]) /*参数个数，参数设备路径/dev/video*/
{
    int fd;

    struct v4l2_fmtdesc fmtdesc;
    int fmt_index = 0;
    int frame_index = 0;
    struct v4l2_frmsizeenum fsenum;
    int buf_cnt;
    int i;
    void *bufs[32]; // 指针数组
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    struct pollfd fds[1];
    char filename[32];
    int file_cnt = 0;

    if (argc != 2)
    {
        printf("Usage: %s <dev>\n", argv[0]);
        return -1;
    }

    // open
    fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        printf("can't open %s\n", argv[1]);
        return -1;
    }

    /* 查询能力 */
    struct v4l2_capability cap;
    memset(&cap, 0, sizeof(struct v4l2_capability)); // 将cap清零

    if (0 == ioctl(fd, VIDIOC_QUERYCAP, &cap)) // 查询能力
    {
        if ((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0) // 是否是捕获设备
        {
            fprintf(stderr, "Error opening device %s: video capture not supported.\n",
                    argv[1]);
            return -1;
        }

        if (!(cap.capabilities & V4L2_CAP_STREAMING)) // 是否支持mmap的方式读取，若不支持改为read的方式
        {
            fprintf(stderr, "%s does not support streaming i/o\n", argv[1]);
            return -1;
        }
    }
    else // 失败返回
    {
        printf("can not get capability\n");
        return -1;
    }

    while (1) // 循环枚举格式
    {
        /*枚举格式*/
        fmtdesc.index = fmt_index;                     // 从0开始
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;    // type视频捕获
        if (0 != ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc)) // 枚举格式
        {
            printf("VIDIOC_ENUM_FMT failed\n");
            break;
        }

        frame_index = 0; // 当前格式的每种帧大小枚举
        while (1)        // 循环枚举帧大小
        {
            // 枚举这种格式支持的帧大小
            memset(&fsenum, 0, sizeof(struct v4l2_frmsizeenum));
            fsenum.pixel_format = fmtdesc.pixelformat; // pixel_format: 使用当前格式的像素格式
            fsenum.index = frame_index;                // 当前的索引

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

    // 设置格式
    struct v4l2_format fmt;
    memset(&fmt, 0, sizeof(struct v4l2_format));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;       // 视频捕获类型
    fmt.fmt.pix.width = 1024;                     // 设置宽度
    fmt.fmt.pix.height = 768;                     // 设置高度
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG; // 设置像素格式MJPEG
    fmt.fmt.pix.field = V4L2_FIELD_ANY;           // 设置扫描方式
    if (0 == ioctl(fd, VIDIOC_S_FMT, &fmt))       // 设置格式成功
    {
        printf("set format ok: %d x %d\n", fmt.fmt.pix.width, fmt.fmt.pix.height);
    }
    else // 失败，可能不支持格式
    {
        printf("can not set format\n");
        return -1;
    }

    /*
     * 申请buffer
     */
    struct v4l2_requestbuffers rb;
    memset(&rb, 0, sizeof(struct v4l2_requestbuffers));
    rb.count = 32; // 申请buffer个数
    rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    rb.memory = V4L2_MEMORY_MMAP; // 使用内存映射mmap

    if (0 == ioctl(fd, VIDIOC_REQBUFS, &rb)) // 申请buffer成功
    {
        /* 申请成功后, mmap这些buffer */
        buf_cnt = rb.count;            // 实际分配的buffer个数，不一定等于你请求的数量
        for (i = 0; i < rb.count; i++) // 逐个映射每个buffer到用户空间
        {
            struct v4l2_buffer buf; // 查询每个buffer的信息
            memset(&buf, 0, sizeof(struct v4l2_buffer));
            buf.index = i;                             // 缓冲区索引
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;    // 类型
            buf.memory = V4L2_MEMORY_MMAP;             // 捕获映射方式
            if (0 == ioctl(fd, VIDIOC_QUERYBUF, &buf)) // 发送 VIDIOC_QUERYBUF 请求，查询buffer信息，结果保存到buf中
            {
                /* mmap */
                bufs[i] = mmap(0 /* start anywhere */,
                               buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
                               buf.m.offset); // 映射到用户空间
                if (bufs[i] == MAP_FAILED)    // 若失败
                {
                    perror("Unable to map buffer");
                    return -1;
                }
            }
            else // VIDIOC_QUERYBUF 查询失败，说明缓冲区状态异常
            {
                printf("can not query buffer\n");
                return -1;
            }
        }

        printf("map %d buffers ok\n", buf_cnt); // 显示成功映射buffer数量
    }
    else // 分配buffer失败
    {
        printf("can not request buffers\n");
        return -1;
    }

    /* 把所有buffer放入"空闲链表" */
    for (i = 0; i < buf_cnt; ++i)
    {
        struct v4l2_buffer buf;
        memset(&buf, 0, sizeof(struct v4l2_buffer));
        buf.index = i;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        if (0 != ioctl(fd, VIDIOC_QBUF, &buf)) // 放入空闲链表
        {
            perror("Unable to queue buffer");
            return -1;
        }
    }
    printf("queue buffers ok\n");

    /* 启动摄像头 */
    /* STREAMON  │ 开始采集
     * DQBUF 取出图像帧
     *QBUF 放回缓冲区
     */
    if (0 != ioctl(fd, VIDIOC_STREAMON, &type)) // 将数据采集到缓冲区
    {
        perror("Unable to start capture");
        return -1;
    }
    printf("start capture ok\n");

    //创建线程用来控制亮度
    pthread_t thread;
    pthread_create(&thread, NULL, thread_brightness_control, (void *)fd);

    while (1) // 循环采集数据
    {
        /* poll */
        memset(fds, 0, sizeof(fds));
        fds[0].fd = fd;
        fds[0].events = POLLIN;    // 数据可读是唤醒
        if (1 == poll(fds, 1, -1)) // 表示有数据，等待采集完数据
        {
            /* 把buffer取出队列 */
            struct v4l2_buffer buf; // 初始化，准备从队列中取出数据
            memset(&buf, 0, sizeof(struct v4l2_buffer));
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;

            if (0 != ioctl(fd, VIDIOC_DQBUF, &buf)) // 从就绪队列中取出缓冲区
            {
                perror("Unable to dequeue buffer");
                return -1;
            }

            /* 把buffer的数据存为文件 */
            sprintf(filename, "video_raw_data_%04d.jpg", file_cnt++); // 将图像保存成文件
            int fd_file = open(filename, O_RDWR | O_CREAT, 0666);     // 创建文件，打印文件名
            if (fd_file < 0)
            {
                printf("can not create file : %s\n", filename);
            }
            printf("capture to %s\n", filename);
            write(fd_file, bufs[buf.index], buf.bytesused); // 将缓冲区图像写入文件
            close(fd_file);

            /* 把buffer放入队列 */
            if (0 != ioctl(fd, VIDIOC_QBUF, &buf)) // 将缓冲区重新入队到空闲队列，为下一帧数据准备
            {
                perror("Unable to queue buffer");
                return -1;
            }
        }
    }

    if (0 != ioctl(fd, VIDIOC_STREAMOFF, &type)) // 停止采集，缓冲区不能使用
    {
        perror("Unable to stop capture");
        return -1;
    }
    printf("stop capture ok\n");
    close(fd);

    return 0;
}