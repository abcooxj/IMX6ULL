#include "mainwindow.h"

#include <QApplication>

/*
 *  文件命名都是小写字母
 * 类的名字首字母是大写，单词于单词之间首字母是大写的
 * 除了构造函数和析构函数成员函数的首字母都是小写的，单词和单词之间首字母是大写的
 * 变量的首写字母都是小写的，单词和单词之间首字母都是大写的
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
