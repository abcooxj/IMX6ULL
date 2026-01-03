#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 设置串口参数
    serial.setPortName("/dev/ttymxc2");
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    // 打开串口
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "串口打开失败:" << serial.errorString();
    } else {
        connect(&serial, &QSerialPort::readyRead, this, &Widget::onSerialDataReceived);
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QByteArray dataToSend = "11";

    serial.write(dataToSend);
     qDebug() << "send:" << dataToSend;
}

void Widget::onSerialDataReceived()
{
    QByteArray receivedData = serial.readAll();
    qDebug() << "recv:" << receivedData;

    // 显示到 QLabel 上（作为字符串）
    ui->label->setText(QString::fromUtf8(receivedData));
}
