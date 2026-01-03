#ifndef MYWIDGE_H
#define MYWIDGE_H

#include <QWidget>

class MyWidge : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidge(QWidget *parent = nullptr);
    ~MyWidge();

signals:

};

#endif // MYWIDGE_H
