#include "mywidge.h"
#include <QDebug>

MyWidge::MyWidge(QWidget *parent) : QWidget(parent)
{

}

MyWidge::~MyWidge()
{
    qDebug()<<"mywidge被执行le"<<endl;
}
