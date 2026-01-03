#include "widget.h"
#include "ui_widget.h"
#include "qqitem.h"

#include <QListWidgetItem>
class QQitem;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QQitem *qqItem = new QQitem(":/icons/icon1.jpg", true, "风子兰特");

     QQitem *qqItem1 = new QQitem(":/icons/icon0.jpg", false, "LIYOU");
     QQitem *qqItem2 = new QQitem(":/icons/icon2.jpg", false, "简单一点");
     QQitem *qqItem3 = new QQitem(":/icons/icon3.jpg", true, "Nov");

       QListWidgetItem *item0 = new QListWidgetItem;
       QListWidgetItem *item1 = new QListWidgetItem;
       QListWidgetItem *item2 = new QListWidgetItem;
       QListWidgetItem *item3 = new QListWidgetItem;

       ui->listWidget->addItem(item0);
       ui->listWidget->addItem(item1);
       ui->listWidget->addItem(item2);
       ui->listWidget->addItem(item3);

       ui->listWidget->setItemWidget(item0, qqItem);
       ui->listWidget->setItemWidget(item1, qqItem1);
       ui->listWidget->setItemWidget(item2, qqItem2);
       ui->listWidget->setItemWidget(item3, qqItem3);

}

Widget::~Widget()
{
    delete ui;
}

