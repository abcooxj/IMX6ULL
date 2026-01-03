#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    client=new QMqttClient;
    //连接阿里云服务器
    m_strProductKey="k1oa7spTciQ";                          //需要跟阿里云Iot平台一致;
    m_strDeviceName="Device1";                              //需要跟阿里云Iot平台一致;
    m_strDeviceSecret="c4bc7e2f4c84705f1584b95c28d053a6";   //需要跟阿里云平台一致
    m_strRegionId="cn-shanghai";
}

Widget::~Widget()
{
    delete ui;
}

