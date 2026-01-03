#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);//隐藏界面的边框，无边框
    setAttribute(Qt::WA_TranslucentBackground);//将背景设置为透明的
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    this->close();
}

void Dialog::on_pushButton_2_clicked()
{
        this->close();
}
