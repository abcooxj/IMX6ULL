#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pushButton=new QPushButton(this);
    //pushButton->show();
    pushButton->setText("按钮");
    pushButton->setGeometry(50,150,100,50);
    this->resize(800,480);
}

MainWindow::~MainWindow()
{
}

