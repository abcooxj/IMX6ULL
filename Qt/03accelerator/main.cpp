#include "mainwindow.h"

#include <QApplication>
/*
 *新建项目,ctrl+n
 * 运行项目，ctrl+r
 * 构建项目，ctrl+b
 * 改变编辑器界面字体比例大小，ctrl+鼠标滚轮
 * 对齐代码，ctrl+a;ctrl+i
 * 跳转到上一行，ctrl+shift+enter
 * 跳转到下一行，ctrl+enter
 * 向上移动行，ctrl+shift+up
 * 向下移动行，ctrl+shift+down
 * 复制当前行到上一行, ctrl+shift+pgup
 * 复制当前行到下一行, ctrl+shift+pgdown
 * 进入类型层次显示基类和派生类，选中QMainWindow按下ctrl+shift+T
 * 切换源文件和头文件，F4
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
