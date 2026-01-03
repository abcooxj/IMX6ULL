/********************************************************************************
** Form generated from reading UI file 'showphoto.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWPHOTO_H
#define UI_SHOWPHOTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_showphoto
{
public:
    QPushButton *pushButton_back;
    QPushButton *pushButton_front;
    QPushButton *pushButton_next;
    QLabel *label;

    void setupUi(QWidget *showphoto)
    {
        if (showphoto->objectName().isEmpty())
            showphoto->setObjectName(QString::fromUtf8("showphoto"));
        showphoto->resize(1024, 600);
        pushButton_back = new QPushButton(showphoto);
        pushButton_back->setObjectName(QString::fromUtf8("pushButton_back"));
        pushButton_back->setGeometry(QRect(0, 0, 80, 100));
        pushButton_front = new QPushButton(showphoto);
        pushButton_front->setObjectName(QString::fromUtf8("pushButton_front"));
        pushButton_front->setGeometry(QRect(0, 280, 80, 100));
        pushButton_front->setMinimumSize(QSize(80, 0));
        pushButton_next = new QPushButton(showphoto);
        pushButton_next->setObjectName(QString::fromUtf8("pushButton_next"));
        pushButton_next->setGeometry(QRect(950, 280, 80, 100));
        label = new QLabel(showphoto);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 0, 850, 610));
        label->setStyleSheet(QString::fromUtf8("background-color:rgb(85, 87, 83)"));

        retranslateUi(showphoto);

        QMetaObject::connectSlotsByName(showphoto);
    } // setupUi

    void retranslateUi(QWidget *showphoto)
    {
        showphoto->setWindowTitle(QApplication::translate("showphoto", "Form", nullptr));
        pushButton_back->setText(QApplication::translate("showphoto", "\350\277\224\345\233\236", nullptr));
        pushButton_front->setText(QApplication::translate("showphoto", "\344\270\212\344\270\200\345\274\240", nullptr));
        pushButton_next->setText(QApplication::translate("showphoto", "\344\270\213\344\270\200\345\274\240", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class showphoto: public Ui_showphoto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWPHOTO_H
