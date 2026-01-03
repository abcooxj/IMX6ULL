#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mymainwindow.h"//窗口2
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MyMainWindow *ppage2=NULL;//用来保存窗口2的实例化对象地址

private:
    Ui::MainWindow *ui;
    //文件
    int led_fd,sg90_fd;
    QString led_dev = "/dev/newchrled";
    //QString sg90_dev = "/dev/sg90";
    //QString beep_dev ="/dev/beep";
    //QString ap3216_dev = "/dev/ap3216";
    //QString dht11_dev = "/dev/dht11";
    //QString sr501_dev = "/dev/sr501";
    unsigned char buf[10];
};
#endif // MAINWINDOW_H
