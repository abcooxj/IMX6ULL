#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
   client =new QMqttClient;

   client->setHostname("127.0.0.1");
   client->setPort(1883);
   client->setUsername("test");
   client->setPassword("123456");

   //client->connectToHost();
   connect(client,&QMqttClient::connected,this,&Widget::connectSuccessSlot);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_connectButton_clicked()
{
     client->connectToHost();
}

void Widget::connectSuccessSlot()
{
    QMessageBox::information(this,"连接提示","连接成功");
    connect(client,&QMqttClient::messageReceived,this,&Widget::recvMessageSlot);
    connect(client,&QMqttClient::disconnected,[this](){
        QMessageBox::information(this,"连接提示","服务器断开");
    });
}

void Widget::recvMessageSlot(const QByteArray &ba, const QMqttTopicName &topic)
{
    QString str=topic.name()+QString(ba);
    ui->textEdit->setText(str);
}



void Widget::on_subButton_clicked()
{
    client->subscribe(ui->subTopicEdit->text());
}


void Widget::on_pubButton_clicked()
{
    QString msg=ui->msgEdit->text();
    QByteArray ba;
    ba.append(msg);
    client->publish(ui->pubTopicEdit->text(),ba);
}
