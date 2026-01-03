#include "student.h"
#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::comBackToClass()
{
    qDebug()<<"学生上课"<<endl;
}
