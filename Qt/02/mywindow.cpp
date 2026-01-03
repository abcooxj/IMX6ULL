#include "mywindow.h"
#include "ui_mywindow.h"
#include <QDebug>

MyWindow::MyWindow(QWidget *parent)
    : QMainWindow(parent)
    , i(4)//i=4;自己创建的变量
    , ui(new Ui::MyWindow)//ui=new Ui::MyWindow

{
    //i=4;//或者在这里定义也是可以的
    ui->setupUi(this);
    qDebug()<<"构造函数执行了"<<endl;
    //在这里添加自己的代码
}

MyWindow::~MyWindow()
{
    qDebug()<<"析构函数执行了"<<endl;
    delete ui;
}

