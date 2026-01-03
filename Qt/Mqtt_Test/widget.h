#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QtMqtt/qmqttclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
   // void on_pushButton_clicked();

    void connectSuccessSlot();
    void recvMessageSlot(const QByteArray &ba,const QMqttTopicName &topic);

    void on_subButton_clicked();

    void on_connectButton_clicked();

    void on_pubButton_clicked();

private:
    Ui::Widget *ui;
    QMqttClient *client;//声明成员变量
};
#endif // WIDGET_H
