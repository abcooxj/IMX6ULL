#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    school=new School(this);
    student=new Student(this);

    connect(school,SIGNAL(sendMessages()),student,SLOT(comBackToClass()));
    connect(school,SIGNAL(sendMessages()),this,SLOT(hide()));//一个信号连接多个槽
    connect(school,SIGNAL(sendMessages2()),student,SLOT(comBackToClass()));//多个信号连接一个槽
    connect(school, SIGNAL(sendMessages2()), this, SIGNAL(iconSizeChanged()));//一个信号连接另一个信号
    emit school->sendMessages();
}

MainWindow::~MainWindow()
{
    delete ui;
}

