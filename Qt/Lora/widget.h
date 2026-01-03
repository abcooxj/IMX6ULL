#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
     QSerialPort serial;  // 串口对象

private slots:
    void on_pushButton_clicked();
    void onSerialDataReceived();  // 串口数据接收槽

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
