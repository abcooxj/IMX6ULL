/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_3;
    QWidget *YH3;
    QListWidget *listWidget;
    QListWidget *listWidget_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(800, 600);
        scrollArea = new QScrollArea(Dialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(370, 0, 431, 601));
        scrollArea->setStyleSheet(QString::fromUtf8(" QScrollBar:vertical { width: 20px; background: white; }\n"
" QScrollBar::handle:vertical { background:  rgba(200, 200, 200, 50%);border-radius: 5px }\n"
" QScrollBar::handle:vertical:hover { background:  rgba(200, 200, 200, 90%); }\n"
" QScrollBar::add-line:vertical { width: 0px; height: 0px }\n"
" QScrollBar::sub-line:vertical {  width: 0px; height: 0px }"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(-195, -110, 1000, 1000));
        scrollAreaWidgetContents->setMinimumSize(QSize(1000, 1000));
        scrollArea->setWidget(scrollAreaWidgetContents);
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 30, 281, 291));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget { border:none }\n"
"QTabBar::tab { width: 0px; height:0px }"));
        tabWidget->setTabsClosable(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color:red;\n"
"}"));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tab_3->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color:pink\n"
";\n"
"}"));
        tabWidget->addTab(tab_3, QString());
        YH3 = new QWidget();
        YH3->setObjectName(QString::fromUtf8("YH3"));
        YH3->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color:green;\n"
"}"));
        tabWidget->addTab(YH3, QString());
        listWidget = new QListWidget(Dialog);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(20, 350, 111, 241));
        listWidget->setStyleSheet(QString::fromUtf8(" QListView { background-color: #dddddd;  border: none }\n"
" QListView::item {  height: 50px }\n"
" QListView::item:selected {  background-color: white; color: black}"));
        listWidget_2 = new QListWidget(Dialog);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(170, 340, 161, 251));

        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Dialog", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Dialog", "\351\241\2653", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(YH3), QApplication::translate("Dialog", "Tab 2", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(1);
        ___qlistwidgetitem->setText(QApplication::translate("Dialog", "\347\231\273\345\275\225", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(2);
        ___qlistwidgetitem1->setText(QApplication::translate("Dialog", "\347\212\266\346\200\201", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(3);
        ___qlistwidgetitem2->setText(QApplication::translate("Dialog", "\344\274\232\350\257\235\347\252\227\345\217\243", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
