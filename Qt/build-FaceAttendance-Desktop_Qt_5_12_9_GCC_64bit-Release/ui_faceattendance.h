/********************************************************************************
** Form generated from reading UI file 'faceattendance.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEATTENDANCE_H
#define UI_FACEATTENDANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceAttendance
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QWidget *widgetLb;
    QLabel *label;
    QLabel *label_2;
    QLabel *headpicLb;
    QLabel *videoLb;
    QWidget *widget_3;
    QLabel *titleLb;
    QLabel *headLb;
    QWidget *widget_4;
    QLabel *label_6;
    QLineEdit *numberEdit;
    QWidget *widget_5;
    QLabel *label_8;
    QLineEdit *nameEdit;
    QWidget *widget_6;
    QLabel *label_10;
    QLineEdit *departmentEdit;
    QWidget *widget_7;
    QLabel *label_12;
    QLineEdit *timeEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FaceAttendance)
    {
        if (FaceAttendance->objectName().isEmpty())
            FaceAttendance->setObjectName(QString::fromUtf8("FaceAttendance"));
        FaceAttendance->resize(800, 480);
        centralwidget = new QWidget(FaceAttendance);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 480, 450));
        widget->setStyleSheet(QString::fromUtf8(""));
        widgetLb = new QWidget(widget);
        widgetLb->setObjectName(QString::fromUtf8("widgetLb"));
        widgetLb->setGeometry(QRect(100, 330, 301, 61));
        widgetLb->setStyleSheet(QString::fromUtf8("background-color: rgba(136, 138, 133,0.4)"));
        label = new QLabel(widgetLb);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 0, 231, 61));
        QFont font;
        font.setPointSize(24);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(136, 138, 133,0.2);\n"
"color: rgb(238, 238, 236);\n"
"border:none;\n"
"border-radius:12px;"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(widgetLb);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 70, 60));
        label_2->setMinimumSize(QSize(21, 21));
        label_2->setStyleSheet(QString::fromUtf8("border-image:url(:/yes.png)"));
        headpicLb = new QLabel(widget);
        headpicLb->setObjectName(QString::fromUtf8("headpicLb"));
        headpicLb->setGeometry(QRect(110, 50, 266, 266));
        headpicLb->setMinimumSize(QSize(266, 266));
        headpicLb->setStyleSheet(QString::fromUtf8("background-image:url(:/crc.png)"));
        videoLb = new QLabel(widget);
        videoLb->setObjectName(QString::fromUtf8("videoLb"));
        videoLb->setGeometry(QRect(0, 0, 480, 480));
        videoLb->raise();
        widgetLb->raise();
        headpicLb->raise();
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(480, -20, 320, 480));
        widget_3->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border:1px solid #313236;\n"
"	border-radius:4px;\n"
"background-color:rgb(228, 182, 182);\n"
"}"));
        titleLb = new QLabel(widget_3);
        titleLb->setObjectName(QString::fromUtf8("titleLb"));
        titleLb->setGeometry(QRect(20, 20, 271, 41));
        QFont font1;
        font1.setPointSize(20);
        titleLb->setFont(font1);
        titleLb->setStyleSheet(QString::fromUtf8("color:rgb(238, 238, 236)"));
        titleLb->setAlignment(Qt::AlignCenter);
        headLb = new QLabel(widget_3);
        headLb->setObjectName(QString::fromUtf8("headLb"));
        headLb->setGeometry(QRect(90, 70, 150, 150));
        headLb->setStyleSheet(QString::fromUtf8("border-radius:75px;"));
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(20, 220, 271, 41));
        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 0, 61, 41));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(16);
        label_6->setFont(font2);
        label_6->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255)"));
        numberEdit = new QLineEdit(widget_4);
        numberEdit->setObjectName(QString::fromUtf8("numberEdit"));
        numberEdit->setGeometry(QRect(60, 0, 211, 41));
        QFont font3;
        font3.setPointSize(15);
        numberEdit->setFont(font3);
        numberEdit->setAlignment(Qt::AlignCenter);
        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(20, 280, 271, 41));
        label_8 = new QLabel(widget_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(0, 0, 61, 41));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setFont(font2);
        label_8->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255)"));
        nameEdit = new QLineEdit(widget_5);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setGeometry(QRect(60, 0, 211, 41));
        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(20, 340, 271, 41));
        label_10 = new QLabel(widget_6);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 0, 61, 41));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setFont(font2);
        label_10->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255)"));
        departmentEdit = new QLineEdit(widget_6);
        departmentEdit->setObjectName(QString::fromUtf8("departmentEdit"));
        departmentEdit->setGeometry(QRect(60, 0, 211, 41));
        widget_7 = new QWidget(widget_3);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setGeometry(QRect(20, 400, 271, 41));
        label_12 = new QLabel(widget_7);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(0, 0, 61, 41));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setFont(font2);
        label_12->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255)"));
        timeEdit = new QLineEdit(widget_7);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(60, 0, 211, 41));
        FaceAttendance->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FaceAttendance);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        FaceAttendance->setMenuBar(menubar);
        statusbar = new QStatusBar(FaceAttendance);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FaceAttendance->setStatusBar(statusbar);

        retranslateUi(FaceAttendance);

        QMetaObject::connectSlotsByName(FaceAttendance);
    } // setupUi

    void retranslateUi(QMainWindow *FaceAttendance)
    {
        FaceAttendance->setWindowTitle(QApplication::translate("FaceAttendance", "FaceAttendance", nullptr));
        label->setText(QApplication::translate("FaceAttendance", "\350\256\244\350\257\201\346\210\220\345\212\237", nullptr));
        label_2->setText(QString());
        headpicLb->setText(QString());
        videoLb->setText(QString());
        titleLb->setText(QApplication::translate("FaceAttendance", "\344\272\272\350\204\270\350\257\206\345\210\253\350\200\203\345\213\244\347\263\273\347\273\237", nullptr));
        headLb->setText(QString());
        label_6->setText(QApplication::translate("FaceAttendance", "\345\267\245\345\217\267", nullptr));
        numberEdit->setText(QApplication::translate("FaceAttendance", "00001", nullptr));
        label_8->setText(QApplication::translate("FaceAttendance", "\345\247\223\345\220\215", nullptr));
        label_10->setText(QApplication::translate("FaceAttendance", "\351\203\250\351\227\250", nullptr));
        label_12->setText(QApplication::translate("FaceAttendance", "\346\227\266\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FaceAttendance: public Ui_FaceAttendance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEATTENDANCE_H
