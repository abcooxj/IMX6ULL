#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_radioButton_toggled(bool checked)
{
    qDebug()<<"男"<<checked<<endl;
}

void Widget::on_radioButton_2_toggled(bool checked)
{
    qDebug()<<"女"<<checked<<endl;
}

void Widget::on_checkBox_stateChanged(int arg1)
{
    switch(arg1)
    {
    case Qt::Checked:
           qDebug() << "选中的状态" << endl;
           break;
       case Qt::PartiallyChecked:
           qDebug() << "半选中的状态" << endl;
           break;
       case Qt::Unchecked:
           qDebug() << "未选中的状态" << endl;
           break;

    }
}
