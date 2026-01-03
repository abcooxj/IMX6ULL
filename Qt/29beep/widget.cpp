#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //ui->setupUi(this);
    /* 获取屏幕的分辨率*/
    QList <QScreen *> list_screen = QGuiApplication::screens();
    /* 如果是 ARM 平台，直接设置大小为屏幕的大小 */
    #if __arm__
    /* 重设大小 */
    this->resize(list_screen.at(0)->geometry().width(),
    list_screen.at(0)->geometry().height());
    #else
    /* 否则则设置主窗体大小为 800x480 */
    this->resize(800, 480);
    #endif
    pushButton=new QPushButton(this);
    //居中显示
    pushButton->setMinimumSize(200,50);
    //pushButton->setGeometry((this->width() - pushButton->width()) /2 ,
    //(this->height() - pushButton->height()) /2,
    //pushButton->width(),
    //pushButton->height()
    //);
    pushButton->move(100,100);
    //beep控制接口
    file.setFileName("/sys/devices/platform/leds/leds/beep/brightness");
    if (!file.exists())
    /* 设置按钮的初始化文本 */
    pushButton->setText("未获取到 BEEP 设备！ ");
    /* 获取 BEEP 的状态 */
    getBeepState();
    /* 信号槽连接 */
    connect(pushButton, SIGNAL(clicked()),this, SLOT(pushButtonClicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setBeepState()
{
    //设置beep状态先读取
    bool state=getBeepState();
    //如果文件不存在，返回
    if(!file.exists())
    {
        return;
    }
    if(!file.open(QIODevice::ReadWrite))
        qDebug()<<file.errorString();
    QByteArray buf[2] = {"0", "1"};

    if (state)
    file.write(buf[0]);
    else
    file.write(buf[1]);

    file.close();
    getBeepState();
}

bool Widget::getBeepState()
{
    /* 如果文件不存在，则返回 */
    if (!file.exists())
    return false;
    if(!file.open(QIODevice::ReadWrite))
    qDebug()<<file.errorString();
    QTextStream in(&file);
    /* 读取文件所有数据 */
    QString buf = in.readLine();
    /* 打印出读出的值 */
    qDebug()<<"buf: "<<buf<<endl;
    file.close();
    if (buf == "1") {
        pushButton->setText("BEEP 开");
        return true;
        } else {
        pushButton->setText("BEEP 关");
        return false;
        }
}

void Widget::pushButtonClicked()
{
/* 设置蜂鸣器的状态 */
setBeepState();
}
