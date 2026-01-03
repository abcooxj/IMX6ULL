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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 60, 221, 331));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"      border-image: url(:/icon/\343\200\220\345\223\262\351\243\216\345\243\201\347\272\270\343\200\221\345\260\221\345\245\263-\347\214\253.png);\n"
" } "));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(360, 70, 421, 501));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"      border-image: url(:/icon/\343\200\220\345\223\262\351\243\216\345\243\201\347\272\270\343\200\221\344\272\221\345\275\251-\345\244\234\347\251\272-\346\234\210\344\272\256.png);\n"
"		color:red;\n"
"	font-size:30pt;\n"
" } "));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label->setText(QString());
        label_2->setText(QApplication::translate("Widget", "\350\265\233\350\277\252\345\223\246\346\230\257\346\236\201\345\244\247\347\240\264\344\270\207\345\244\247\346\226\207\345\214\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
