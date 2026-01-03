#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <sys/mman.h>
#include <signal.h>
#include <poll.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <string.h>

#include <QTimer>
#include <showphoto.h>

#define		video_width		640
#define 	video_height	480

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();



private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_photos_clicked();

    void on_pushButton_take_clicked();

private:
    Ui::Widget *ui;

    char *userbuff[4];//存放映射后的内存地址
    int userbuff_length[4];//保存映射后的数据长度

    int show_flag=1;//1保存到本地，0显示到lcd
    int video_fd;
    int lcd_fd;
    int lcd_xres, lcd_yres;
    int lcd_realvirtual;

    int start = 0;

    QTimer *timer;

    int v4l2_open();
    int v4l2_close();

public slots:
    void video_show();

};
#endif // WIDGET_H
