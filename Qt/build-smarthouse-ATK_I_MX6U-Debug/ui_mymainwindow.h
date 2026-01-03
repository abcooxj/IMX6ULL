/********************************************************************************
** Form generated from reading UI file 'mymainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMAINWINDOW_H
#define UI_MYMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyMainWindow
{
public:
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *people;
    QPushButton *pushButton_5;
    QLabel *label_4;
    QWidget *layoutWidget1;
    QHBoxLayout *temp_all;
    QPushButton *pushButton_6;
    QLabel *label_5;
    QWidget *layoutWidget2;
    QHBoxLayout *sun_all;
    QPushButton *pushButton_7;
    QLabel *label_6;
    QWidget *layoutWidget3;
    QHBoxLayout *beep_all;
    QPushButton *pushButton_3;
    QLabel *label_2;
    QWidget *layoutWidget4;
    QHBoxLayout *light_all;
    QPushButton *pushButton_2;
    QLabel *label;
    QWidget *layoutWidget_2;
    QHBoxLayout *water;
    QPushButton *pushButton_8;
    QLabel *label_7;
    QLabel *label_9;
    QWidget *widget_6;
    QWidget *widget_3;
    QWidget *layoutWidget5;
    QVBoxLayout *time_all;
    QLabel *label_3;
    QLabel *label_8;
    QWidget *layoutWidget6;
    QHBoxLayout *curtain;
    QHBoxLayout *hlayout_4;
    QWidget *widget_5;
    QPushButton *pushButton_4;
    QVBoxLayout *verticalLayout_10;
    QProgressBar *progressBar;
    QSlider *horizontalSlider;
    QLabel *label_10;

    void setupUi(QWidget *MyMainWindow)
    {
        if (MyMainWindow->objectName().isEmpty())
            MyMainWindow->setObjectName(QString::fromUtf8("MyMainWindow"));
        MyMainWindow->resize(1024, 600);
        MyMainWindow->setMinimumSize(QSize(2, 80));
        QFont font;
        font.setFamily(QString::fromUtf8("Purisa"));
        font.setPointSize(50);
        font.setItalic(true);
        MyMainWindow->setFont(font);
        MyMainWindow->setStyleSheet(QString::fromUtf8("QWidget { \n"
"		background-color: white;\n"
"\n"
"\n"
"};"));
        pushButton = new QPushButton(MyMainWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 480, 111, 80));
        pushButton->setMinimumSize(QSize(80, 80));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"		 border-image:url(:/icons/Snipaste.png)\n"
"\n"
"};"));
        layoutWidget = new QWidget(MyMainWindow);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(740, 190, 228, 102));
        people = new QHBoxLayout(layoutWidget);
        people->setObjectName(QString::fromUtf8("people"));
        people->setContentsMargins(0, 0, 0, 0);
        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(100, 100));
        pushButton_5->setMaximumSize(QSize(100, 100));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"		 border-image:url(:/icons/peo.png)\n"
"\n"
"};"));

        people->addWidget(pushButton_5);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(120, 80));
        QFont font1;
        font1.setPointSize(18);
        label_4->setFont(font1);

        people->addWidget(label_4);

        layoutWidget1 = new QWidget(MyMainWindow);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(390, 190, 228, 102));
        temp_all = new QHBoxLayout(layoutWidget1);
        temp_all->setObjectName(QString::fromUtf8("temp_all"));
        temp_all->setContentsMargins(0, 0, 0, 0);
        pushButton_6 = new QPushButton(layoutWidget1);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(100, 100));
        pushButton_6->setMaximumSize(QSize(100, 100));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"		 border-image:url(:/icons/temperature.jpg)\n"
"\n"
"};"));

        temp_all->addWidget(pushButton_6);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(120, 80));
        label_5->setFont(font1);

        temp_all->addWidget(label_5);

        layoutWidget2 = new QWidget(MyMainWindow);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(390, 330, 228, 102));
        sun_all = new QHBoxLayout(layoutWidget2);
        sun_all->setObjectName(QString::fromUtf8("sun_all"));
        sun_all->setContentsMargins(0, 0, 0, 0);
        pushButton_7 = new QPushButton(layoutWidget2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(100, 100));
        pushButton_7->setMaximumSize(QSize(100, 100));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"		 border-image:url(:/icons/sun.jpeg)\n"
"\n"
"};"));

        sun_all->addWidget(pushButton_7);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(120, 80));
        label_6->setFont(font1);

        sun_all->addWidget(label_6);

        layoutWidget3 = new QWidget(MyMainWindow);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(60, 330, 228, 102));
        beep_all = new QHBoxLayout(layoutWidget3);
        beep_all->setObjectName(QString::fromUtf8("beep_all"));
        beep_all->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(100, 100));
        pushButton_3->setMaximumSize(QSize(100, 100));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"		 border-image:url(:/icons/beep.jpg)\n"
"\n"
"};"));
        pushButton_3->setCheckable(true);

        beep_all->addWidget(pushButton_3);

        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(120, 80));
        label_2->setFont(font1);

        beep_all->addWidget(label_2);

        layoutWidget4 = new QWidget(MyMainWindow);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(60, 190, 228, 102));
        light_all = new QHBoxLayout(layoutWidget4);
        light_all->setObjectName(QString::fromUtf8("light_all"));
        light_all->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(100, 100));
        pushButton_2->setMaximumSize(QSize(100, 100));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"		 border-image:url(:/icons/light.jpg)\n"
"\n"
"};"));
        pushButton_2->setCheckable(true);

        light_all->addWidget(pushButton_2);

        label = new QLabel(layoutWidget4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(120, 80));
        label->setFont(font1);

        light_all->addWidget(label);

        layoutWidget_2 = new QWidget(MyMainWindow);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(740, 330, 228, 102));
        water = new QHBoxLayout(layoutWidget_2);
        water->setObjectName(QString::fromUtf8("water"));
        water->setContentsMargins(0, 0, 0, 0);
        pushButton_8 = new QPushButton(layoutWidget_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(100, 100));
        pushButton_8->setMaximumSize(QSize(100, 100));
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"		 border-image:url(:/icons/ee1.png)\n"
"\n"
"};"));

        water->addWidget(pushButton_8);

        label_7 = new QLabel(layoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(120, 80));
        label_7->setFont(font1);

        water->addWidget(label_7);

        label_9 = new QLabel(MyMainWindow);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(490, 50, 200, 100));
        label_9->setMinimumSize(QSize(200, 100));
        label_9->setMaximumSize(QSize(200, 100));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Purisa"));
        font2.setPointSize(53);
        font2.setItalic(false);
        font2.setKerning(true);
        label_9->setFont(font2);
        widget_6 = new QWidget(MyMainWindow);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(696, 21, 2, 160));
        widget_6->setMinimumSize(QSize(2, 140));
        widget_6->setMaximumSize(QSize(2, 200));
        widget_6->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	background-color:gray\n"
"};"));
        widget_3 = new QWidget(MyMainWindow);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(20, 10, 441, 171));
        widget_3->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	 border-image:url(:/icons/tele.jpg)\n"
"}"));
        layoutWidget5 = new QWidget(MyMainWindow);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(720, 20, 252, 153));
        time_all = new QVBoxLayout(layoutWidget5);
        time_all->setObjectName(QString::fromUtf8("time_all"));
        time_all->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(250, 80));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Purisa"));
        font3.setPointSize(56);
        font3.setItalic(false);
        font3.setKerning(true);
        label_3->setFont(font3);

        time_all->addWidget(label_3);

        label_8 = new QLabel(layoutWidget5);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(250, 65));
        label_8->setMaximumSize(QSize(250, 160));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Purisa"));
        font4.setPointSize(18);
        font4.setItalic(true);
        label_8->setFont(font4);
        label_8->setAlignment(Qt::AlignCenter);

        time_all->addWidget(label_8);

        layoutWidget6 = new QWidget(MyMainWindow);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(171, 471, 618, 104));
        curtain = new QHBoxLayout(layoutWidget6);
        curtain->setObjectName(QString::fromUtf8("curtain"));
        curtain->setContentsMargins(0, 0, 0, 0);
        hlayout_4 = new QHBoxLayout();
        hlayout_4->setObjectName(QString::fromUtf8("hlayout_4"));
        widget_5 = new QWidget(layoutWidget6);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));

        hlayout_4->addWidget(widget_5);

        pushButton_4 = new QPushButton(layoutWidget6);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(100, 100));
        pushButton_4->setMaximumSize(QSize(100, 100));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"		 border-image:url(:/icons/cur.jpeg)\n"
"\n"
"};"));

        hlayout_4->addWidget(pushButton_4);


        curtain->addLayout(hlayout_4);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        progressBar = new QProgressBar(layoutWidget6);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(500, 20));
        progressBar->setValue(24);

        verticalLayout_10->addWidget(progressBar);

        horizontalSlider = new QSlider(layoutWidget6);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimumSize(QSize(500, 20));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_10->addWidget(horizontalSlider);


        curtain->addLayout(verticalLayout_10);

        label_10 = new QLabel(MyMainWindow);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(800, 470, 120, 100));
        label_10->setMinimumSize(QSize(120, 80));
        label_10->setFont(font1);

        retranslateUi(MyMainWindow);

        QMetaObject::connectSlotsByName(MyMainWindow);
    } // setupUi

    void retranslateUi(QWidget *MyMainWindow)
    {
        MyMainWindow->setWindowTitle(QApplication::translate("MyMainWindow", "Form", nullptr));
        pushButton->setText(QString());
        pushButton_5->setText(QString());
        label_4->setText(QApplication::translate("MyMainWindow", "0", nullptr));
        pushButton_6->setText(QString());
        label_5->setText(QApplication::translate("MyMainWindow", "0", nullptr));
        pushButton_7->setText(QString());
        label_6->setText(QApplication::translate("MyMainWindow", "0", nullptr));
        pushButton_3->setText(QString());
        label_2->setText(QApplication::translate("MyMainWindow", "\345\205\263", nullptr));
        pushButton_2->setText(QString());
        label->setText(QApplication::translate("MyMainWindow", "\345\274\200", nullptr));
        pushButton_8->setText(QString());
        label_7->setText(QApplication::translate("MyMainWindow", "0", nullptr));
        label_9->setText(QApplication::translate("MyMainWindow", "Room", nullptr));
        label_3->setText(QApplication::translate("MyMainWindow", "12:00", nullptr));
        label_8->setText(QApplication::translate("MyMainWindow", "2025-04-30 \346\230\237\346\234\237\344\272\224", nullptr));
        pushButton_4->setText(QString());
        label_10->setText(QApplication::translate("MyMainWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyMainWindow: public Ui_MyMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMAINWINDOW_H
