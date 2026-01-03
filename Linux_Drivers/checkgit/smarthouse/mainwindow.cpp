#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mymainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ppage2=new MyMainWindow;//实例化窗口2

    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        //切换窗口，本身是隐藏切换出去的窗口，显示切换到的窗口2
        this->hide();//仅仅隐藏，并没有释放主窗口页面
        this->ppage2->show();//显示窗口2
    });

    connect(this->ppage2,&MyMainWindow::back,[=](){
        //不想这样可以单独写槽函数
        this->ppage2->hide();
        this->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}



