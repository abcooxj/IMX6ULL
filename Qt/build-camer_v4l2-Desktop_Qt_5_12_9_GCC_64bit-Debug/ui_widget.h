/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_open;
    QPushButton *pushButton_photos;
    QPushButton *pushButton_take;
    QPushButton *pushButton_back;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1024, 600);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 850, 610));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54);"));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(851, 0, 171, 601));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_open = new QPushButton(layoutWidget);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));
        pushButton_open->setMinimumSize(QSize(150, 60));

        verticalLayout->addWidget(pushButton_open);

        pushButton_photos = new QPushButton(layoutWidget);
        pushButton_photos->setObjectName(QString::fromUtf8("pushButton_photos"));
        pushButton_photos->setMinimumSize(QSize(150, 60));

        verticalLayout->addWidget(pushButton_photos);

        pushButton_take = new QPushButton(layoutWidget);
        pushButton_take->setObjectName(QString::fromUtf8("pushButton_take"));
        pushButton_take->setMinimumSize(QSize(150, 60));

        verticalLayout->addWidget(pushButton_take);

        pushButton_back = new QPushButton(layoutWidget);
        pushButton_back->setObjectName(QString::fromUtf8("pushButton_back"));
        pushButton_back->setMinimumSize(QSize(150, 60));

        verticalLayout->addWidget(pushButton_back);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label->setText(QApplication::translate("Widget", "\346\230\276\347\244\272\345\214\272\345\237\237", nullptr));
        pushButton_open->setText(QApplication::translate("Widget", "\346\211\223\345\274\200", nullptr));
        pushButton_photos->setText(QApplication::translate("Widget", "\347\233\270\345\206\214", nullptr));
        pushButton_take->setText(QApplication::translate("Widget", "\346\213\215\347\205\247", nullptr));
        pushButton_back->setText(QApplication::translate("Widget", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
