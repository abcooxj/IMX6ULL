/********************************************************************************
** Form generated from reading UI file 'qqitem.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QQITEM_H
#define UI_QQITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QQitem
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QWidget *widget1;
    QLabel *icon;
    QLabel *phone;
    QLabel *name;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *QQitem)
    {
        if (QQitem->objectName().isEmpty())
            QQitem->setObjectName(QString::fromUtf8("QQitem"));
        QQitem->resize(400, 300);
        widget = new QWidget(QQitem);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 20, 391, 52));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget1 = new QWidget(widget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setMinimumSize(QSize(48, 48));
        widget1->setMaximumSize(QSize(48, 48));
        icon = new QLabel(widget1);
        icon->setObjectName(QString::fromUtf8("icon"));
        icon->setGeometry(QRect(0, 0, 48, 48));
        icon->setMinimumSize(QSize(48, 48));
        icon->setMaximumSize(QSize(48, 48));
        icon->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color:gray;\n"
"}"));
        phone = new QLabel(widget1);
        phone->setObjectName(QString::fromUtf8("phone"));
        phone->setGeometry(QRect(20, 20, 25, 25));
        phone->setMinimumSize(QSize(25, 25));
        phone->setMaximumSize(QSize(25, 25));
        phone->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color:white;\n"
"}"));

        horizontalLayout->addWidget(widget1);

        name = new QLabel(widget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color:darkgray;font-size:20px;\n"
"}"));

        horizontalLayout->addWidget(name);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        retranslateUi(QQitem);

        QMetaObject::connectSlotsByName(QQitem);
    } // setupUi

    void retranslateUi(QWidget *QQitem)
    {
        QQitem->setWindowTitle(QApplication::translate("QQitem", "Form", nullptr));
        icon->setText(QString());
        phone->setText(QString());
        name->setText(QApplication::translate("QQitem", "\344\275\240\345\245\275\351\207\214\351\273\204\345\272\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QQitem: public Ui_QQitem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QQITEM_H
