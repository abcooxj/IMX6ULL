#ifndef FACEATTENDANCE_H
#define FACEATTENDANCE_H

#include <QMainWindow>
#include <opencv.hpp>
#include <QTcpSocket>
#include <QTimer>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class FaceAttendance; }
QT_END_NAMESPACE

class FaceAttendance : public QMainWindow
{
    Q_OBJECT

public:
    FaceAttendance(QWidget *parent = nullptr);
    ~FaceAttendance();
    //为了让摄像头实时显示，定义一个定时器
    void timerEvent(QTimerEvent *e) ;

protected slots:
    void recv_data();
    void onSocketError(QAbstractSocket::SocketError err);
private slots:
    void timer_connect();//连接
    void stop_connect();//停止连接
    void start_connect();//开始连接

private:
    Ui::FaceAttendance *ui;
    //摄像头
    VideoCapture cap;
    //进行人脸检测，创建一个haar级联分类器
    cv::CascadeClassifier cascade;

    //创建一个网络套接字,定时器
    QTcpSocket msocket;
    QTimer mtimer;

    //标志是否是同一个人脸进入设备
    int flag;

    //保存人脸的数据
    cv::Mat faceMat;
};
#endif // FACEATTENDANCE_H
