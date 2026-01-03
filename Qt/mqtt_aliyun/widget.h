#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QtMqtt/qmqttclient.h"
#include <QJsonObject>

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
    void connectSuccessSlot();
    void recvMessageSlot(const QByteArray &ba, const QMqttTopicName &topic);

    void on_pushButton_clicked();
    void dht11_send();

private:
    Ui::Widget *ui;
    QMqttClient *client;//声明成员变量
    QString m_strPubTopic;
    QString m_strProductKey;
    QString m_strDeviceName;
    QString m_strDeviceSecret;
    QString m_strRegionId;

    QString m_strSubTopic;
    QString m_strTargetServer;
    QJsonObject jsonObj;
};
#endif // WIDGET_H
