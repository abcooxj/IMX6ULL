#ifndef SCHOOL_H
#define SCHOOL_H

#include <QObject>

class School : public QObject
{
    Q_OBJECT
public:
    explicit School(QObject *parent = nullptr);

signals://Qt信号的关键字,只声明不用定义
    void sendMessages();
    void sendMessages2();

};

#endif // SCHOOL_H
