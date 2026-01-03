#include "registerwin.h"
#include "ui_registerwin.h"
#include <QFileDialog>
#include <qfaceobject.h>
#include <QSqlTableModel>//数据库模型
#include <QSqlRecord>//记录
#include <QMessageBox>//注册成功，弹出小框
#include <QDebug>

RegisterWin::RegisterWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWin)
{
    ui->setupUi(this);
}

RegisterWin::~RegisterWin()
{
    delete ui;
}

void RegisterWin::timerEvent(QTimerEvent *e)//刷新摄像头数据
{
    //获取摄像头数据并且显示在界面
    //cv::Mat image;
    cap>>image;//获取一阵数据
    if(image.data==nullptr)return;

    //Mat->QImage
    cv::Mat rgbImage;
    cv::cvtColor(image,rgbImage,cv::COLOR_BGR2RGB);
    QImage qImg(image.data,image.cols,image.rows,image.step1(),QImage::Format_RGB888);
    //在QT中显示
    QPixmap mmp=QPixmap::fromImage(qImg);
    mmp=mmp.scaledToWidth(ui->headpicLb->width());
    ui->headpicLb->setPixmap(mmp);
}

void RegisterWin::on_resetBt_clicked()
{
    //清空数据
    ui->nameEdit->clear();
    ui->birthdayEdit->setDate(QDate::currentDate());
    ui->addressEdirt->clear();
    ui->phoneEdirt->clear();
    ui->picFileEdirt->clear();
}


void RegisterWin::on_addpicBt_clicked()
{
    //通过文件对话框，选中图片路径
    QString filepath= QFileDialog::getOpenFileName(this);
    ui->headpicLb->setText(filepath);

    //显示图片
    QPixmap mmp(filepath);
    mmp=mmp.scaledToHeight(ui->headpicLb->width());
    ui->headpicLb->setPixmap(mmp);

}


#if 0
void RegisterWin::on_addpicBt_clicked()
{
    // 1. 打开文件对话框，限制图片格式
    QString filepath = QFileDialog::getOpenFileName(
        this,
        "选择头像",
        "",
        "图片文件 (*.jpg *.jpeg *.png *.bmp)" // 只让选图片，减少错误
    );

    // 2. 处理用户取消选择（避免空路径）
    if (filepath.isEmpty()) {
        QMessageBox::information(this, "提示", "已取消选择图片");
        return;
    }

    // 3. 关键：将路径同步到 picFileEdirt 输入框（之前遗漏或未生效的核心步骤）
    ui->picFileEdirt->setText(filepath);  // 这行必须有！！！

    // 4. 加载并显示图片（验证图片有效性）
    QPixmap mmp(filepath);
    if (mmp.isNull()) {
        QMessageBox::warning(this, "错误", "图片加载失败！文件损坏或格式不支持");
        ui->picFileEdirt->clear(); // 清空无效路径
        ui->headpicLb->setText("图片加载失败");
        return;
    }

    // 5. 缩放显示（保持比例）
    mmp = mmp.scaled(ui->headpicLb->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->headpicLb->setPixmap(mmp);
    ui->headpicLb->setText(""); // 清空标签文本
}
#endif


void RegisterWin::on_registerBt_clicked()
{
    //1.通过照片，结合faceObject模块得到faceID
    QFaceObject  faceobj;//创建一个对象
    cv::Mat image = cv::imread(ui->picFileEdirt->text().toUtf8().data());//将文件路径数据格式转化char->mat
    int faceID = faceobj.face_register(image);//获取人脸数据id
    qDebug()<<faceID;//打印faceid

    //把头像保存到一个固定路径下
    QString headfile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    cv::imwrite(headfile.toUtf8().data(), image);//将图片保存到文件，写入

    //2.把个人信息存储到数据库employee
    QSqlTableModel model;
    model.setTable("employee");//设置表名
    QSqlRecord record=model.record();
    //设置数据
    record.setValue("name",ui->nameEdit->text());
    record.setValue("sex",ui->mrb->isChecked()?"男":"女");
    record.setValue("birthday", ui->birthdayEdit->text());
    record.setValue("address",ui->addressEdirt->text());
    record.setValue("phone",ui->phoneEdirt->text());
    record.setValue("faceID", faceID);

    //头像路径
    record.setValue("headfile",headfile);
    //把记录插入到数据库表格中
    bool ret = model.insertRecord(0,record);

    //3.提示注册成功
    if(ret)
    {
        QMessageBox::information(this,"注册提示","注册成功");
        //提交
        model.submitAll();
    }else
    {
        QMessageBox::information(this,"注册提示","注册失败");
    }
}


#if 0
void RegisterWin::on_registerBt_clicked()
{
    // ======================== 前置检查：拦截所有可能导致空图像的情况 ========================
    // 1. 检查姓名不为空
    QString name = ui->nameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "提示", "姓名不能为空！");
        return;
    }

    // 2. 检查图片路径不为空（二次确认）
    QString picPath = ui->picFileEdirt->text().trimmed();
    if (picPath.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择头像图片！");
        return;
    }

    // 3. 读取图片并强制检查是否为空（核心拦截点）
    cv::Mat image = cv::imread(picPath.toUtf8().data());
    if (image.empty()) {  // 这行是阻止崩溃的最后一道防线！
        QMessageBox::critical(this, "致命错误",
            QString("图片读取失败，无法注册！\n请检查：\n1. 路径是否正确：%1\n2. 文件是否损坏\n3. 是否有读取权限").arg(picPath));
        return; // 直接终止，不执行后续写入操作
    }

    // ======================== 后续人脸注册、写入图片、数据库操作 ========================
    QFaceObject faceobj;
    int faceID = -1;
    try {
        faceID = faceobj.face_register(image);
    } catch (const cv::Exception& e) {
        QMessageBox::critical(this, "人脸注册错误", e.what());
        return;
    }

    // 检查人脸注册是否成功（-1 通常表示无人脸）
    if (faceID < 0) {
        QMessageBox::warning(this, "提示", "未检测到人脸，请选择清晰的人脸图片！");
        return;
    }
    qDebug() << "faceID：" << faceID;

    // 保存头像（此时 image 已确认非空，可安全写入）
    QDir dataDir("./data");
    if (!dataDir.exists()) dataDir.mkpath("."); // 创建目录
    QString headfile = QString("./data/%1_%2.jpg").arg(name).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    if (!cv::imwrite(headfile.toUtf8().data(), image)) {
        QMessageBox::warning(this, "提示", "头像保存失败，但个人信息已注册！");
    }

    // 数据库操作（略，保持原逻辑，注意检查数据库连接）
    // ...
}
#endif

void RegisterWin::on_videoswitchBt_clicked()
{
    if(ui->videoswitchBt->text()=="打开摄像头")
    {
        //打开摄像头
        if(cap.open("/dev/video0", cv::CAP_V4L2))
        {
        ui->videoswitchBt->setText("关闭摄像头");
        //启动定时器事件
        timerid=startTimer(100);
        }
    }
    else
    {
        //关闭定时器事件
        killTimer(timerid);
        ui->videoswitchBt->setText("打开摄像头");
        //关闭摄像头
        cap.release();
    }
}


#if 0
void RegisterWin::on_videoswitchBt_clicked()
{
    if (ui->videoswitchBt->text() == "打开摄像头")
    {
        // 1. 先检查摄像头是否已打开（避免重复打开）
        if (cap.isOpened())
        {
            QMessageBox::warning(this, "提示", "摄像头已打开！");
            return;
        }

        // 2. 尝试打开摄像头（多路径+多后端，提升兼容性）
        bool openOk = cap.open("/dev/video0") || cap.open("/dev/video0", cv::CAP_V4L2) || cap.open("/dev/video1");
        if (!openOk)
        {
            QMessageBox::critical(this, "错误", "无法打开摄像头！\n请检查设备连接和权限");
            return; // 打开失败，不执行后续操作
        }

        // 3. 启动定时器（先停止旧定时器，避免冲突）
        if (timerid != -1)
        {
            killTimer(timerid);
            timerid = -1;
        }
        timerid = startTimer(100); // 此时 timerid 为有效ID
        ui->videoswitchBt->setText("关闭摄像头");
        qDebug() << "[摄像头] 打开成功，定时器ID：" << timerid;
    }
    else
    {
        // 4. 关闭定时器（必须检查 timerid 有效性！）
        if (timerid != -1)
        {
            killTimer(timerid);
            timerid = -1; // 重置为无效值
            qDebug() << "[摄像头] 定时器关闭";
        }

        // 5. 释放摄像头（必须检查是否已打开！）
        if (cap.isOpened())
        {
            cap.release();
            qDebug() << "[摄像头] 设备释放";
        }

        ui->videoswitchBt->setText("打开摄像头");
        ui->headpicLb->clear();
        ui->headpicLb->setText("摄像头已关闭");
    }
}
#endif

void RegisterWin::on_cameraBt_clicked()
{
    //保存数据
    //把头像保存到一个固定路径下
    QString headfile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    ui->picFileEdirt->setText(headfile);
    cv::imwrite(headfile.toUtf8().data(), image);
    //关闭定时器事件
    killTimer(timerid);
    ui->videoswitchBt->setText("打开摄像头");
    //关闭摄像头
    cap.release();
}
