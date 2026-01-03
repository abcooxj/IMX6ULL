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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *connectButton;
    QLabel *label;
    QTextEdit *textEdit;
    QPushButton *subButton;
    QLineEdit *subTopicEdit;
    QLineEdit *pubTopicEdit;
    QLineEdit *msgEdit;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pubButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        connectButton = new QPushButton(Widget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(250, 140, 241, 91));
        QFont font;
        font.setPointSize(18);
        connectButton->setFont(font);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 350, 301, 41));
        QFont font1;
        font1.setPointSize(20);
        label->setFont(font1);
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 410, 761, 171));
        subButton = new QPushButton(Widget);
        subButton->setObjectName(QString::fromUtf8("subButton"));
        subButton->setGeometry(QRect(440, 270, 91, 51));
        subTopicEdit = new QLineEdit(Widget);
        subTopicEdit->setObjectName(QString::fromUtf8("subTopicEdit"));
        subTopicEdit->setGeometry(QRect(30, 270, 341, 51));
        pubTopicEdit = new QLineEdit(Widget);
        pubTopicEdit->setObjectName(QString::fromUtf8("pubTopicEdit"));
        pubTopicEdit->setGeometry(QRect(120, 10, 191, 41));
        msgEdit = new QLineEdit(Widget);
        msgEdit->setObjectName(QString::fromUtf8("msgEdit"));
        msgEdit->setGeometry(QRect(120, 50, 191, 51));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 10, 67, 17));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 70, 67, 17));
        pubButton = new QPushButton(Widget);
        pubButton->setObjectName(QString::fromUtf8("pubButton"));
        pubButton->setGeometry(QRect(350, 30, 91, 51));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        connectButton->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        label->setText(QApplication::translate("Widget", "\346\224\266\345\210\260\346\234\215\345\212\241\345\231\250\346\216\250\351\200\201\346\266\210\346\201\257", nullptr));
        subButton->setText(QApplication::translate("Widget", "\350\256\242\351\230\205", nullptr));
        label_2->setText(QApplication::translate("Widget", "\344\270\273\351\242\230", nullptr));
        label_3->setText(QApplication::translate("Widget", "\345\206\205\345\256\271", nullptr));
        pubButton->setText(QApplication::translate("Widget", "\345\217\221\345\270\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
