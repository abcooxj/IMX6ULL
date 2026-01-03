#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //添加列表项
    ui->listWidget_2->addItem("张三");
    ui->listWidget_2->addItem("张4");

    // 移除项
        ui->listWidget->takeItem(0);

    // 插入项，从项前面插入
    ui->listWidget->insertItem(0, "张三");
}

Dialog::~Dialog()
{
    delete ui;
}

/*关闭界面*/
void Dialog::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void Dialog::on_listWidget_currentRowChanged(int currentRow)
{
    ui->tabWidget->setCurrentIndex(currentRow);
}

void Dialog::on_listWidget_2_currentRowChanged(int currentRow)
{
    qDebug() << "下标是：" << currentRow << "项的内容是："  << ui->listWidget_2->item(currentRow)->text() << endl;

}
