#include "faceattendance.h"
#include "ui_faceattendance.h"
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

FaceAttendance::FaceAttendance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FaceAttendance)
{
    ui->setupUi(this);
    //msocket = new QTcpSocket(this);
    //打开摄像头
    cap.open("/dev/video0", cv::CAP_V4L2);//linux下。dev/video,强制指定V4L2接口
    //启动定时器事件
    startTimer(300);//100刷新太快，占用内存

    //导入级联分类器
    cascade.load("/home/abcooxj/opencv/Face_opencv4_up/opencv-4.5.2/install/share/opencv4/haarcascades/haarcascade_frontalface_alt2.xml");


    //QTsocket当断开连接disconnected信号，连接成功会发送connected
    connect(&msocket,&QTcpSocket::disconnected,this,&FaceAttendance::start_connect);
    connect(&msocket,&QTcpSocket::connected,this,&FaceAttendance::stop_connect);

    //关联接收数据的槽函数
    //connect(&msocket,&QTcpSocket::readyRead,this,&FaceAttendance::recv_data);
    bool isConnSuccess = connect(&msocket, &QTcpSocket::readyRead, this, &FaceAttendance::recv_data);
    if (!isConnSuccess) {
        qDebug() << "错误：readyRead信号与recv_data槽连接失败！";
    }

    // ========== 修改5：增加Socket错误提示（定位连接问题） ==========
    connect(&msocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSocketError(QAbstractSocket::SocketError)));

    //定时器连接服务器
    connect(&mtimer,&QTimer::timeout,this,&FaceAttendance::timer_connect);
    //启动定时器
    mtimer.start(5000);//每5秒连接一次，直到连接成功

    flag=0;
    ui->widgetLb->hide();//隐藏
}

FaceAttendance::~FaceAttendance()
{
    delete ui;

#if 0
    if (cap.isOpened()) {  // 释放摄像头资源
            cap.release();
            qDebug() << "摄像头资源已释放";
        }
        if (msocket.state() != QAbstractSocket::UnconnectedState) {  // 断开Socket连接
            msocket.disconnectFromHost();
            qDebug() << "Socket连接已断开";
        }

   #endif
}

void FaceAttendance::onSocketError(QAbstractSocket::SocketError err)
{
    qDebug() << "Socket错误：" << msocket.errorString();
}

void FaceAttendance::timerEvent(QTimerEvent *e)
{
    // ========== 修改7：先检查摄像头是否打开，避免空指针错误 ==========
       if (!cap.isOpened()) {
           return;  // 摄像头未打开，直接退出
       }

    //采集数据
    Mat srcImage;//定义一个采集原始数据
    if(cap.grab())//判断是否有数据
    {
        cap.read(srcImage);//读取一帧数据
    }

    //把图片大小设与显示窗口一样大
    cv::resize(srcImage,srcImage,Size(480,480));

    // ========== 修改8：检查图像是否有效，避免后续处理崩溃 ==========
        if (srcImage.empty()) {
            qDebug() << "警告：未读取到摄像头图像";
            return;
        }

    //将图像转为灰度图，一般传入灰度数据,会提高检测速度
    Mat grayImage;
    cvtColor(srcImage,grayImage,COLOR_RGB2GRAY);
    //检测人脸数据
    std::vector<Rect> faceRects;
    //cascade.detectMultiScale(srcImage，faceRects);
    cascade.detectMultiScale(grayImage,faceRects);
    if(faceRects.size()>0&&flag>=0)//检测到人脸
    {

        Rect rect =faceRects.at(0);//第一个人脸的矩形框
        //画出人脸框,(矩形)
        //rectangle(srcImage,rect,Scalar(0,0,255));
        //移动人脸框(图片-QLabel)
        ui->headpicLb->move(rect.x,rect.y);

       if(flag>2){
        //把MAT数据转化为QbyteArray,-->编码成jpg格式
        std::vector<uchar> buf;//动态数组
        cv::imencode(".jpg",srcImage,buf);//srcImage编码生成的数据存入buf中
        QByteArray byte((const char*)buf.data(),buf.size());//将uchar转换为QbyteArray类型
        //准备发送，发送文件
        quint64 backsize=byte.size();//获取文件大小
        QByteArray sendData;
        QDataStream steam(&sendData,QIODevice::WriteOnly);
        steam.setVersion(QDataStream::Qt_5_12);
        steam<<backsize<<byte;//先接收图片大小再收数据
        //发送
        msocket.write(sendData);
        flag=-2;

        faceMat=srcImage(rect);
        //保存人脸数据
        imwrite("./face.jpg",faceMat);

       }
        flag++;

    }
    //else{
    if(faceRects.size()==0){
        //没有人脸时，将人脸框移动到中心位置
        ui->headpicLb->move(100,60);
        flag=0;
    }

    if(srcImage.data==nullptr)
    {
       return;
    }
    //将opencv中的mat格式数据（RGB）转成QT里面QImage(RGB)
    cvtColor(srcImage,srcImage,COLOR_BGR2RGB);
    QImage image(srcImage.data,srcImage.cols,srcImage.rows,srcImage.step1(),QImage::Format_RGB888);
    QPixmap mmp=QPixmap::fromImage(image);
    //mmp=mmp.scaledToWidth(ui->videoLb->width());//缩放
    ui->videoLb->setPixmap(mmp);
}

void FaceAttendance::recv_data()
{
    qDebug()<<"被调了";

#if 0
    // ========== 修改16：先检查Socket连接状态，再读取数据 ==========
       if (msocket.state() != QAbstractSocket::ConnectedState) {
           qDebug() << "recv_data：Socket已断开，无法读取数据";
           return;
       }

    //疑点，.和->的区别
    QString msg = msocket.readAll();
    qDebug()<<"收到数据："<<msg;
    ui->lineEdit->setText(msg);
#endif

    //{employeeID:%1,name:%2,department:软件,time:%3}
    QByteArray array = msocket.readAll();
    qDebug()<<array;
    //Json解析
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(array,&err);//如果json数据有错误，会将错误填入err
    if(err.error != QJsonParseError::NoError)
    {
        qDebug()<<"json数据错误";
        return;
    }
    QJsonObject obj = doc.object();
    QString employeeID = obj.value("employeeID").toString();
    QString name = obj.value("name").toString();
    QString department = obj.value("department").toString();
    QString timestr = obj.value("time").toString();

    ui->numberEdit->setText(employeeID);
    ui->nameEdit->setText(name);
    ui->departmentEdit->setText(department);
    ui->timeEdit->setText(timestr);

    qDebug()<<"工号"<<employeeID;
    qDebug()<<timestr;

    //通过样式来显示图片
    ui->headLb->setStyleSheet("border-radius:75px;border-image: url(./face.jpg);");
    ui->widgetLb->show();

}

void FaceAttendance::timer_connect()
{
    //连接服务器
    msocket.connectToHost("192.168.200.130",9999);
    qDebug()<<"正在连接服务器";
}

void FaceAttendance::stop_connect()
{
    mtimer.stop();
    qDebug()<<"成功连接服务器";
}

void FaceAttendance::start_connect()
{
    mtimer.start(5000);//启动定时器，进行定时器连接服务器
    qDebug()<<"断开连接";
}
