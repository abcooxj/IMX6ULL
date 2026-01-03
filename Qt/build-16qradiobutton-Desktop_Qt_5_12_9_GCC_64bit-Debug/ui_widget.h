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
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QPushButton *pushButton_4;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;
    QButtonGroup *buttonGroup_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        radioButton = new QRadioButton(Widget);
        buttonGroup_2 = new QButtonGroup(Widget);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->addButton(radioButton);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(20, 22, 100, 50));
        radioButton_2 = new QRadioButton(Widget);
        buttonGroup_2->addButton(radioButton_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(20, 100, 111, 51));
        radioButton_3 = new QRadioButton(Widget);
        buttonGroup = new QButtonGroup(Widget);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->setExclusive(false);
        buttonGroup->addButton(radioButton_3);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(210, 32, 121, 41));
        radioButton_4 = new QRadioButton(Widget);
        buttonGroup->addButton(radioButton_4);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(210, 100, 121, 51));
        radioButton_5 = new QRadioButton(Widget);
        buttonGroup->addButton(radioButton_5);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(210, 150, 121, 51));
        radioButton_6 = new QRadioButton(Widget);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setGeometry(QRect(0, 170, 131, 111));
        pushButton = new QPushButton(Widget);
        buttonGroup_3 = new QButtonGroup(Widget);
        buttonGroup_3->setObjectName(QString::fromUtf8("buttonGroup_3"));
        buttonGroup_3->addButton(pushButton);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 330, 221, 71));
        pushButton->setCheckable(true);
        pushButton_2 = new QPushButton(Widget);
        buttonGroup_3->addButton(pushButton_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 410, 221, 71));
        pushButton_2->setCheckable(true);
        pushButton_3 = new QPushButton(Widget);
        buttonGroup_3->addButton(pushButton_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 510, 221, 61));
        pushButton_3->setCheckable(true);
        checkBox = new QCheckBox(Widget);
        buttonGroup_4 = new QButtonGroup(Widget);
        buttonGroup_4->setObjectName(QString::fromUtf8("buttonGroup_4"));
        buttonGroup_4->setExclusive(false);
        buttonGroup_4->addButton(checkBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(500, 60, 92, 23));
        checkBox->setTristate(true);
        checkBox_2 = new QCheckBox(Widget);
        buttonGroup_4->addButton(checkBox_2);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(500, 100, 92, 23));
        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(250, 230, 511, 321));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton { margin: 50px ; \n"
"background-color: #CDCDB4 ;\n"
"border-width: 50px;\n"
"border-color: #458B00;\n"
"border-style: solid;\n"
"padding: 100px;\n"
"}"));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        radioButton->setText(QApplication::translate("Widget", "\347\224\267", nullptr));
        radioButton_2->setText(QApplication::translate("Widget", "\345\245\263", nullptr));
        radioButton_3->setText(QApplication::translate("Widget", "\350\257\255\346\226\207", nullptr));
        radioButton_4->setText(QApplication::translate("Widget", "\346\225\260\345\255\246", nullptr));
        radioButton_5->setText(QApplication::translate("Widget", "\345\234\260\347\220\206", nullptr));
        radioButton_6->setText(QApplication::translate("Widget", "RadioButton", nullptr));
        pushButton->setText(QApplication::translate("Widget", "PushButton", nullptr));
        pushButton_2->setText(QApplication::translate("Widget", "PushButton", nullptr));
        pushButton_3->setText(QApplication::translate("Widget", "PushButton", nullptr));
        checkBox->setText(QApplication::translate("Widget", "\344\270\211\346\200\201\351\200\211\346\213\251", nullptr));
        checkBox_2->setText(QApplication::translate("Widget", "\345\244\215\351\200\211", nullptr));
        pushButton_4->setText(QApplication::translate("Widget", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
