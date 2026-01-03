#include "attendancewin.h"
#include "attendancewin.h"
#include "ui_attendancewin.h"
#include <QDateTime>
#include <QSqlRecord>
#include <QThread>
#include <opencv.hpp>
#include <QSqlQuery>
#include <QSqlError>

AttendanceWin::AttendanceWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AttendanceWin)
{
    ui->setupUi(this);
    //qtserver当有客户端连接会发送newconnection，server只能用于连接，不能进行收发数据
    connect(&mserver, &QTcpServer::newConnection, this, &AttendanceWin::accept_client);//192.168.200.129
    mserver.listen(QHostAddress::Any,9999);//监听，启动服务器
    bsize=0;

    //给模型sql绑定表格
    model.setTable("employee");

    //创建一个线程实现人脸识别
    QThread *thread=new QThread;
    //把QFaceObject对象移动到thread线程中执行
    fobj.moveToThread(thread);
    //启动线程
    thread->start();
    connect(this,&AttendanceWin::query,&fobj,&QFaceObject::face_query);
    //关联QFaceObject对象里面的send_faceid信号
    connect(&fobj,&QFaceObject::send_faceid,this, &AttendanceWin::recv_faceid);

}

AttendanceWin::~AttendanceWin()
{
    delete ui;
}

//接受客户端连接
void AttendanceWin::accept_client()
{
    //获取客户端通信的套接字
    msocket=mserver.nextPendingConnection();

    //当客户端有数据到达，会发送readyRead信号
    connect(msocket,&QTcpSocket::readyRead,this,&AttendanceWin::read_data);
}

//读取客户端发送数据
void AttendanceWin::read_data()
{
    //读取所言的数据
    //QString msg = msocket->readAll();
    //qDebug()<<msg;

    QDataStream steam(msocket);//把套接字绑定到数据流
    steam.setVersion(QDataStream::Qt_5_12);
    if(bsize==0)
    {
        if(msocket->bytesAvailable()<(quint64)sizeof(bsize)) return;//小于
        //大于，采集数据长度
        steam>>bsize;
    }
    if(msocket->bytesAvailable() <bsize)//说明数据没有发送完成。返回等待
    {
        return;
    }

    QByteArray data;
    steam>>data;//这是的数据是jpg数据
    bsize=0;
    if(data.size()==0)//没有读取到数据
    {
        return;
    }

    //显示图片
    QPixmap mmp;
    mmp.loadFromData(data,"jpg");
    mmp=mmp.scaled(ui->picLb->size());
    ui->picLb->setPixmap(mmp);

    //识别人脸
    cv::Mat faceImage;
    //qt中的数据是QByteArray data;需要转换为
    std::vector<uchar> decode;
    decode.resize(data.size());
    memcpy(decode.data(),data.data(),data.size());//将data的数据拷贝到decode中
    //解码
    faceImage=cv::imdecode(decode,cv::IMREAD_COLOR);


    //int faceid=fobj.face_query(faceImage);//消耗资源多，使用线程优化
    emit query(faceImage);



}

void AttendanceWin::recv_faceid(int64_t faceid)
{
    qDebug()<<"识别到的人脸"<<faceid;

    if(faceid<0)
    {
        QString sdmsg = QString("{\"employeeID\":\" \",\"name\":\"\",\"department\":\"\",\"time\":\"\"}");
        msocket->write(sdmsg.toUtf8());//把打包好的数据发送给客户端
        return ;
    }

    //从数据库中查询faceid对应的人脸数据
    //设置过滤器
    model.setFilter(QString ("faceID=%1").arg(faceid));
    //查询
    model.select();
    qDebug()<<"查询数据。。。";
    //判断是否查询到数据
    if(model.rowCount()==1)
    {
        //将数据打包固定格式传回客户端，工号，姓名，部门，时间
        //{employeeID:%1,name:%2,department:软件,time:%3}
        QSqlRecord record = model.record(0);
        //打包数据
        qDebug()<<"开始打包数据";
        QString sdmsg = QString("{\"employeeID\":\"%1\",\"name\":\"%2\",\"department\":\"软件\",\"time\":\"%3\"}")
                .arg(record.value("employeeID").toString()).arg(record.value("name").toString())
                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        //msocket->write(sdmsg.toUtf8());//把打包好的数据发送给客户端

        //把数据写入数据库--考勤表
        QString insertSql = QString("insert into attendance(employeeID) values('%1')").arg(record.value("employeeID").toString());
        QSqlQuery query;
        if(!query.exec(insertSql))
        {
            QString sdmsg = QString("{\"employeeID\":\" \",\"name\":\"\",\"department\":\"\",\"time\":\"\"}");
            msocket->write(sdmsg.toUtf8());//把打包好的数据发送给客户端
            qDebug()<<query.lastError().text();//查错
            return ;
        }else
        {
            msocket->write(sdmsg.toUtf8());//把打包好的数据发送给客户端
        }
    }
}
