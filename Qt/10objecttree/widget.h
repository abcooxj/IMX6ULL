#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "mywidge.h"

class MyWidge;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QPushButton *pushButton;
    MyWidge *myWidget;
};
#endif // WIDGET_H
