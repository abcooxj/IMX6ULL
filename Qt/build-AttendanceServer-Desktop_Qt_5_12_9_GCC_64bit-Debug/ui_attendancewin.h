/********************************************************************************
** Form generated from reading UI file 'attendancewin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTENDANCEWIN_H
#define UI_ATTENDANCEWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AttendanceWin
{
public:
    QWidget *centralwidget;
    QLabel *picLb;

    void setupUi(QMainWindow *AttendanceWin)
    {
        if (AttendanceWin->objectName().isEmpty())
            AttendanceWin->setObjectName(QString::fromUtf8("AttendanceWin"));
        AttendanceWin->resize(800, 480);
        centralwidget = new QWidget(AttendanceWin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        picLb = new QLabel(centralwidget);
        picLb->setObjectName(QString::fromUtf8("picLb"));
        picLb->setGeometry(QRect(60, 60, 301, 361));
        picLb->setStyleSheet(QString::fromUtf8("background-color:rgb(188, 239, 148);"));
        AttendanceWin->setCentralWidget(centralwidget);

        retranslateUi(AttendanceWin);

        QMetaObject::connectSlotsByName(AttendanceWin);
    } // setupUi

    void retranslateUi(QMainWindow *AttendanceWin)
    {
        AttendanceWin->setWindowTitle(QApplication::translate("AttendanceWin", "AttendanceWin", nullptr));
        picLb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AttendanceWin: public Ui_AttendanceWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTENDANCEWIN_H
