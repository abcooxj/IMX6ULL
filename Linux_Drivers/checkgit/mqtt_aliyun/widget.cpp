#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QMessageAuthenticationCode>
#include <QJsonParseError>
#include <QJsonObject>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    client =new QMqttClient;

    //连接阿里云服务器
    m_strProductKey="k1h0ji2AxBV";                          //需要跟阿里云Iot平台一致;
    m_strDeviceName="smart";                              //需要跟阿里云Iot平台一致;
    m_strDeviceSecret="1b76456dc54ed56a80067c96ad0e4e7b";   //需要跟阿里云平台一致
    m_strRegionId="cn-shanghai";

    m_strPubTopic = "/sys/" + m_strProductKey + "/" + m_strDeviceName + "/thing/event/property/post";  //发布topic
    m_strSubTopic = "/sys/" + m_strProductKey + "/" + m_strDeviceName + "/thing/service/property/set"; //订阅topic
    m_strTargetServer = m_strProductKey + ".iot-as-mqtt." + m_strRegionId + ".aliyuncs.com";           //域名

    client->setHostname(m_strTargetServer);
    client->setPort(1883);

    QString clientId="abcdefg";         //表示客户端ID，建议使用设备的MAC地址或SN码，64字符内。
    QString signmethod = "hmacsha1";    //加密方式
    QString message ="clientId"+clientId+"deviceName"+m_strDeviceName+"productKey"+m_strProductKey;

    client->setUsername(m_strDeviceName + "&" + m_strProductKey);
    //client->setClientId(clientId + "|securemode=3,signmethod=" + signmethod + "|");
    client->setClientId("k1h0ji2AxBV.smart|securemode=2,signmethod=hmacsha256,timestamp=1749720853334|");
    client->setPassword("5bd60f0ecfe41363e63cb492ad4d46813ce76e8cd30c66c656508268276bb805");

    //槽函数连接
    connect(client,&QMqttClient::connected,this,&Widget::connectSuccessSlot);//连接成功转到成功函数
    connect(client, &QMqttClient::disconnected, this, [this]()
       {
           QMessageBox::warning(this, "连接提示", "连接失败");
       });//连接错误
     //connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateChanged(int))); /* 连接QCheckBox的状态改变信号到槽函数  */
}

Widget::~Widget()
{
    delete ui;
}

//连接服务器按键
void Widget::on_pushButton_clicked()
{
    /* 连接服务器 */
    client->connectToHost();
}

void Widget::dht11_send()
{
    QString payload="{\"method\":\"thing.service.property.set\",\"id\":\"640404170\",\"params\":{\"dht11\":80.2},\"version\":\"1.0.0\"}";
    client->publish(m_strPubTopic,payload.toLocal8Bit(),0,true);
}

void Widget::connectSuccessSlot()
{
    QMessageBox::information(this, "连接提示", "连接成功");

    /* 消息接受成功槽函数 */
    connect(client, &QMqttClient::messageReceived, this, &Widget::recvMessageSlot);

    connect(client, &QMqttClient::disconnected, this, [this]()
    {
        QMessageBox::warning(this, "连接提示", "服务器断开");
    });

    dht11_send();
}

void Widget::recvMessageSlot(const QByteArray &ba, const QMqttTopicName &topic)
{
    // 解析JSON数据
   QJsonParseError json_error;
   QJsonDocument doc = QJsonDocument::fromJson(ba, &json_error);
   if (json_error.error != QJsonParseError::NoError) {
        // qDebug() << "JSON parse error:" << json_error.errorString();
       return;
   }
   // 检查是否是有效的JSON对象
          if (!doc.isObject()) {
   //           qDebug() << "Invalid JSON object received.";
              return;
          }
          jsonObj = doc.object();

        // 提取方法名
        QString method = jsonObj.value("method").toString();
        if (method != "thing.service.property.set") {
 //           qDebug() << "Unexpected method:" << method;
            return;
        }

        // 提取参数
        QJsonObject params = jsonObj.value("params").toObject();

        /*未完待续*/
}

