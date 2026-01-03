/********************************************************************************
** Form generated from reading UI file 'registerwin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWIN_H
#define UI_REGISTERWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWin
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *nameEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QRadioButton *mrb;
    QRadioButton *wrb;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDateEdit *birthdayEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *addressEdirt;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *phoneEdirt;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *registerBt;
    QPushButton *resetBt;
    QVBoxLayout *verticalLayout_2;
    QLabel *headpicLb;
    QLineEdit *picFileEdirt;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *addpicBt;
    QPushButton *videoswitchBt;
    QPushButton *cameraBt;

    void setupUi(QWidget *RegisterWin)
    {
        if (RegisterWin->objectName().isEmpty())
            RegisterWin->setObjectName(QString::fromUtf8("RegisterWin"));
        RegisterWin->resize(800, 600);
        widget = new QWidget(RegisterWin);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(11, 10, 781, 591));
        horizontalLayout_8 = new QHBoxLayout(widget);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        nameEdit = new QLineEdit(widget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        sizePolicy.setHeightForWidth(nameEdit->sizePolicy().hasHeightForWidth());
        nameEdit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(nameEdit);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        mrb = new QRadioButton(widget);
        mrb->setObjectName(QString::fromUtf8("mrb"));
        sizePolicy.setHeightForWidth(mrb->sizePolicy().hasHeightForWidth());
        mrb->setSizePolicy(sizePolicy);
        mrb->setFont(font);

        horizontalLayout_2->addWidget(mrb);

        wrb = new QRadioButton(widget);
        wrb->setObjectName(QString::fromUtf8("wrb"));
        sizePolicy.setHeightForWidth(wrb->sizePolicy().hasHeightForWidth());
        wrb->setSizePolicy(sizePolicy);
        wrb->setFont(font);

        horizontalLayout_2->addWidget(wrb);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        birthdayEdit = new QDateEdit(widget);
        birthdayEdit->setObjectName(QString::fromUtf8("birthdayEdit"));
        sizePolicy.setHeightForWidth(birthdayEdit->sizePolicy().hasHeightForWidth());
        birthdayEdit->setSizePolicy(sizePolicy);
        birthdayEdit->setFont(font);

        horizontalLayout_4->addWidget(birthdayEdit);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        addressEdirt = new QLineEdit(widget);
        addressEdirt->setObjectName(QString::fromUtf8("addressEdirt"));
        sizePolicy.setHeightForWidth(addressEdirt->sizePolicy().hasHeightForWidth());
        addressEdirt->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(addressEdirt);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setFont(font);

        horizontalLayout_5->addWidget(label_5);

        phoneEdirt = new QLineEdit(widget);
        phoneEdirt->setObjectName(QString::fromUtf8("phoneEdirt"));
        sizePolicy.setHeightForWidth(phoneEdirt->sizePolicy().hasHeightForWidth());
        phoneEdirt->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(phoneEdirt);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        registerBt = new QPushButton(widget);
        registerBt->setObjectName(QString::fromUtf8("registerBt"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(registerBt->sizePolicy().hasHeightForWidth());
        registerBt->setSizePolicy(sizePolicy1);
        registerBt->setFont(font);

        horizontalLayout_7->addWidget(registerBt);

        resetBt = new QPushButton(widget);
        resetBt->setObjectName(QString::fromUtf8("resetBt"));
        sizePolicy1.setHeightForWidth(resetBt->sizePolicy().hasHeightForWidth());
        resetBt->setSizePolicy(sizePolicy1);
        resetBt->setFont(font);

        horizontalLayout_7->addWidget(resetBt);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 2);
        verticalLayout->setStretch(3, 2);
        verticalLayout->setStretch(4, 2);
        verticalLayout->setStretch(5, 2);

        horizontalLayout_8->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        headpicLb = new QLabel(widget);
        headpicLb->setObjectName(QString::fromUtf8("headpicLb"));
        headpicLb->setStyleSheet(QString::fromUtf8("background-color:rgb(149, 180, 123)"));

        verticalLayout_2->addWidget(headpicLb);

        picFileEdirt = new QLineEdit(widget);
        picFileEdirt->setObjectName(QString::fromUtf8("picFileEdirt"));

        verticalLayout_2->addWidget(picFileEdirt);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        addpicBt = new QPushButton(widget);
        addpicBt->setObjectName(QString::fromUtf8("addpicBt"));
        sizePolicy1.setHeightForWidth(addpicBt->sizePolicy().hasHeightForWidth());
        addpicBt->setSizePolicy(sizePolicy1);
        addpicBt->setFont(font);

        horizontalLayout_6->addWidget(addpicBt);

        videoswitchBt = new QPushButton(widget);
        videoswitchBt->setObjectName(QString::fromUtf8("videoswitchBt"));
        sizePolicy1.setHeightForWidth(videoswitchBt->sizePolicy().hasHeightForWidth());
        videoswitchBt->setSizePolicy(sizePolicy1);
        videoswitchBt->setFont(font);

        horizontalLayout_6->addWidget(videoswitchBt);

        cameraBt = new QPushButton(widget);
        cameraBt->setObjectName(QString::fromUtf8("cameraBt"));
        sizePolicy1.setHeightForWidth(cameraBt->sizePolicy().hasHeightForWidth());
        cameraBt->setSizePolicy(sizePolicy1);
        cameraBt->setFont(font);

        horizontalLayout_6->addWidget(cameraBt);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);

        horizontalLayout_8->addLayout(verticalLayout_2);


        retranslateUi(RegisterWin);

        QMetaObject::connectSlotsByName(RegisterWin);
    } // setupUi

    void retranslateUi(QWidget *RegisterWin)
    {
        RegisterWin->setWindowTitle(QApplication::translate("RegisterWin", "Form", nullptr));
        label->setText(QApplication::translate("RegisterWin", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_2->setText(QApplication::translate("RegisterWin", "\346\200\247\345\210\253\357\274\232", nullptr));
        mrb->setText(QApplication::translate("RegisterWin", "\347\224\267", nullptr));
        wrb->setText(QApplication::translate("RegisterWin", "\345\245\263", nullptr));
        label_4->setText(QApplication::translate("RegisterWin", "\347\224\237\346\227\245\357\274\232", nullptr));
        label_3->setText(QApplication::translate("RegisterWin", "\345\234\260\345\235\200\357\274\232", nullptr));
        label_5->setText(QApplication::translate("RegisterWin", "\347\224\265\350\257\235\357\274\232", nullptr));
        registerBt->setText(QApplication::translate("RegisterWin", "\346\263\250\345\206\214", nullptr));
        resetBt->setText(QApplication::translate("RegisterWin", "\351\207\215\347\275\256", nullptr));
        headpicLb->setText(QString());
        addpicBt->setText(QApplication::translate("RegisterWin", "\346\267\273\345\212\240\345\244\264\345\203\217", nullptr));
        videoswitchBt->setText(QApplication::translate("RegisterWin", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", nullptr));
        cameraBt->setText(QApplication::translate("RegisterWin", "\346\213\215\347\205\247", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWin: public Ui_RegisterWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWIN_H
