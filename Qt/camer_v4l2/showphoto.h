#ifndef SHOWPHOTO_H
#define SHOWPHOTO_H

#include <QWidget>
#include <QDir>

namespace Ui {
class showphoto;
}

class showphoto : public QWidget
{
    Q_OBJECT

public:
    explicit showphoto(QWidget *parent = nullptr);
    ~showphoto();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_front_clicked();

    void on_pushButton_next_clicked();

private:
    Ui::showphoto *ui;

    QDir dir; // 目录对象
    QStringList fileList; // 存储文件列表
    int currentIndex = 0; // 当前显示的文件索引
};

#endif // SHOWPHOTO_H
