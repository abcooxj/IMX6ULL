#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QtMqtt/qmqttclient.h"
#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QFile>
#include <QUrlQuery>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include <QTimer>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>

#if defined(Q_OS_ANDROID)
//配置文件名称
#define ConfigFile "/storage/emulated/0/xl_config/cofnig_token.txt"
#else
//配置文件名称
#define ConfigFile "cofnig_token.ini"
#endif


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //将token数据保存到文件
    void SaveDataToFile(QString text);

    //从文件读取token数据
    QString ReadDataFile(void);

    //获取token
    void GetToken();

    //查询设备属性
    void Get_device_properties();

    //日志显示
    void Log_Text_Display(QString text);

    //发送命令
    void MQTT_Cmd_Send(QString cmd);

private slots:
    void data_update();
    void replyFinished(QNetworkReply *reply);
    //更新Token
    void on_pushButton_update_token_clicked();
    //手动获取一次影子数据
    void on_pushButton_update_device_clicked();
    //开启自动更新影子数据
    void on_checkBox_aoto_update_clicked(bool checked);


private:
    Ui::Widget *ui;
    QMqttClient *client;//声明成员变量

    /*
    功能选择
    0表示获取属性
    3表示获取token
    */
    int function_select;
    QByteArray Token; //这是访问的Token
    QNetworkAccessManager *manager;
    QTimer *timer;
    //主账号用户名
    QString MAIN_USER = "abcooxj";
    //IAM子账户用户名--自己创建的
    QString IAM_USER = "mqtt_bxj";
    //IAM子账户密码
    QString IAM_PASSWORD = "DS12345678";
    //项目ID--在我的凭证页面查看
    QString PROJECT_ID = "aa1072427e5f410c8cee5996d952cf51";
    //服务器区域代号--这里以华北-北京四为例
    QString SERVER_ID = "cn-north-4";
    //物联网产品的服务ID
    QString service_id = "Linux";
    //物联网产品的设备ID
    QString device_id = "6840134fd582f200182dec84_dev1";

    //域名,在总览页面可以查看
    //复制过来是这样的 bf6f24d458.st1.iotda-device.cn-north-4.myhuaweicloud.com
    //需要手动修改里面 device --> app
    QString IP_ADDR="bf6f24d458.st1.iotda-device.cn-north-4.myhuaweicloud.com";
};
#endif // WIDGET_H
