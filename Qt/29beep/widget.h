#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    /*按钮*/
    QPushButton *pushButton;
    /*文件*/
    QFile file;
    /*设置 BEEP 的状态 */
    void setBeepState();
    //获取beep状态
    bool getBeepState();

private slots:
    //按键槽函数
    void pushButtonClicked();
};
#endif // WIDGET_H
