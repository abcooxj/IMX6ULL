#include "mymainwindow.h"
#include "ui_mymainwindow.h"

#include <QPushButton>
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <sys/signal.h>

/* 给静态成员函数：sr501_handler 提供全局变量
   否则无法访问到类中的非静态成员变量*/
int temp_sr501_fd;
Ui::MyMainWindow *temp_ui;

MyMainWindow::MyMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMainWindow)
    //timer(12, 0), // 初始化时间为12:00
   //customDate(QDate(2025, 5, 1))
{
    ui->setupUi(this);
    temp_ui = ui;

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        //发个信号过去
        emit this->back();
    });

    //实例化QTimer控件
    //QTimer *timer =new QTimer;
    //connect(timer,SIGNAL(timeout()),this,SLOT(timerTime()));
    //timer->start(1);
    // 在MyMainWindow的构造函数或其他适当的位置
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MyMainWindow::timerTime);
    timer->start(1000); // 设置定时器每1000毫秒（1秒）触发一次

    /* 设置滑动条控制范围 */
     ui->horizontalSlider->setRange(0, 100);
    /* 设置滑动条控制步长 */
     ui->horizontalSlider->setSingleStep(0);
    /* 关闭滑块跟踪：滑块仅在用户释放滑块时才发出valueChanged()信号 */
     ui->horizontalSlider->setTracking(false);

    //led
     led_fd = open(led_dev.toStdString().c_str(), O_RDWR);
         if(led_fd < 0)
             printf("open led failed\n");

    //beep
    /* 开发板的蜂鸣器控制接口 */
    //file.setFileName("/dev/beep");
    beep_fd = open(beep_dev.toStdString().c_str(), O_RDWR);
    if(beep_fd < 0)
        printf("open beep failed\n");

    //ap3216c
    ap3216c_fd=open(ap3216c_dev.toStdString().c_str(),O_RDWR);
    if(ap3216c_fd<0)
        printf("open a3216c failed\n");
    ap3216c_tim=new QTimer();
    ap3216c_tim->setInterval(1000);
    connect(ap3216c_tim,SIGNAL(timeout()),this,SLOT(ap3216c_timeout()));
    ap3216c_tim->start();

    //dht11
    dht11_fd=open(dht11_dev.toStdString().c_str(),O_RDWR);
    if(dht11_fd<0)
        printf("open dht11 failed\n");
    dht11_tim=new QTimer();
    dht11_tim->setInterval(5000);
    connect(dht11_tim,SIGNAL(timeout()),this,SLOT(dht11_timeout()));
    dht11_tim->start();

    //sr501
    sr501_fd = open(sr501_dev.toStdString().c_str(), O_RDWR);
    if(sr501_fd < 0)
        printf("open sr501 failed\n");
    else{
        temp_sr501_fd = sr501_fd;
        // 在文件描述符上设置异步通知
        /* F_SETOWN: 设置将接收SIGIO和SIGURG信号的进程id */
        fcntl(sr501_fd, F_SETOWN, getpid());
        /*  F_GETFL: 取得fd的文件状态标志 */
        sr501_flags = fcntl(sr501_fd, F_GETFL);
        /* O_ASYNC: 当I/O可用的时候,允许SIGIO信号发送到进程组,
           例如:当有数据可以读的时候 */
        fcntl(sr501_fd, F_SETFL, sr501_flags | O_ASYNC);  //启动驱动的fasync功能

        signal(SIGIO, sr501_handler);
        }
    //sg90
    sg90_fd = open(sg90_dev.toStdString().c_str(), O_WRONLY);
        if(sg90_fd < 0)
            printf("open sg90 failed\n");
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}


void MyMainWindow::on_pushButton_2_clicked(bool checked)
{
    qDebug() << checked << endl;
    if(checked)
    {
        buf[0] = 1;
        write(led_fd, buf, 1);
        ui->label->setText("开");
    }
    else
    {
        buf[0] = 0;
        write(led_fd, buf, 1);
        ui->label->setText("关");
    }

}




void MyMainWindow::on_pushButton_3_clicked(bool checked)
{
    qDebug() << checked << endl;

    if(checked)
    {
        buf[0] = 1;
        write(beep_fd, buf, 1);
        ui->label_2->setText("开");
    }
    else
    {
        buf[0] = 0;
        write(beep_fd, buf, 1);
        ui->label_2->setText("关");
    }
}

void MyMainWindow::timerTime()
{
    //获取系统时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QTime currentTime=currentDateTime.time();
    //qDebug() << "当前时间:" << currentTime.toString("hh:mm:ss");
    ui->label_3->setText(currentTime.toString("hh:mm"));
    //ui->label_8->setText(customDate.toString("yy-MM-dd"));
}

void MyMainWindow::on_horizontalSlider_sliderMoved(int position)
{
    int buf[1];
     ui->progressBar->setValue(position);
     //ui->label_10->setText("??");
     buf[0] = ui->progressBar->value();
     buf[0] = 180 / 100.0 * buf[0];
     write(sg90_fd, buf, 1);
}

void MyMainWindow::ap3216c_timeout()
{
    //static int cnt=0;
    unsigned short ir,dis,light;
    read(ap3216c_fd,&buf[1],6);
    if(buf[1]&0x80)
    {
        ir=0;
    }
    else
        ir=(buf[1]<<2)|(buf[2] & 0x03);   /* 读取IR传感器的数据 */

    light = (buf[3] << 8) | buf[4];          /* 读取ALS传感器的数据 */

    if(buf[5] & 0x40)    /* IR_OF位为1,则数据无效 */
        dis = 0;
    else
        dis = ((buf[5] & 0x3f) << 4) | (buf[6] & 0x0f);   /* 读取PS传感器的数据 */
    ui->label_6->setNum(light);
    //qDebug()<<"light:"<<light;
}

void MyMainWindow::dht11_timeout()
{
    unsigned short tmp,hum;
    static int cnt=0;

    read(dht11_fd,buf,4);
    ui->label_5->setNum(buf[2]);
    ui->label_7->setNum(buf[0]);
    qDebug()<<"tmp:"<<buf[2];
    qDebug()<<"hum:"<<buf[0];

}

void MyMainWindow::sr501_handler(int signum)
{
    char val;

    read(temp_sr501_fd, &val, 1);
//    printf("val is %d, %s\n", val, val==1?"have people":"no people");
    temp_ui->label_4->setNum(val);
}


