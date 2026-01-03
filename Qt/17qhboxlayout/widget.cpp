#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout);//让按键大小随窗口的伸缩移动,水平
    //this->setLayout(ui->verticalLayout);//垂直
    //this->setLayout(ui->gridLayout);//网格
    //this->setLayout(ui->horizontalLayout);//分裂器
    //this->setLayout(ui->horizontalLayout);//隔离弹簧水平
    //this->setLayout(ui->verticalLayout);//隔离弹簧垂直
}

Widget::~Widget()
{
    delete ui;
}

