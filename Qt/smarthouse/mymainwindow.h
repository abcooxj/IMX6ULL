#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QTime>
#include <QFile>

namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();

     QTimer* my_timer;


signals:
    void back();//定义一个信号，返回界面


private slots:
    void on_pushButton_2_clicked(bool checked);
    void on_pushButton_3_clicked(bool checked);

    void timerTime();

    void on_horizontalSlider_sliderMoved(int position);
    void ap3216c_timeout();
    void dht11_timeout();



private:
    Ui::MyMainWindow *ui;
    QFile file;
    QTime *timer;
    QDate customDate;
    unsigned char buf[10];
    int sr501_flags;

    int beep_fd;
    int led_fd,ap3216c_fd, dht11_fd,
            sg90_fd, sr501_fd;

    QString led_dev = "/dev/newchrled";
    QString beep_dev = "/dev/beep";
    QString ap3216c_dev="/dev/ap3216c";
    QString dht11_dev="/dev/dht11";
    QString sr501_dev="/dev/sr501";
    QString sg90_dev="/dev/sg90";

    QTimer *ap3216c_tim;
    QTimer *dht11_tim;

    /* 设置成静态成员函数
                C++中类的成员函数默认都提供了this指针，
                在非静态成员函数中当你调用函数的时候，
                编译器都会“自动”帮你把这个this指针加到函数形参里去
           但是 signal 的回调函数只有一个的参数，所以会报错：
                error: reference to non-static member function must be called*/
    static void sr501_handler(int signum);
};

#endif // MYMAINWINDOW_H
