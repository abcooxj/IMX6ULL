#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_tabWidget_tabCloseRequested(int index);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_listWidget_2_currentRowChanged(int currentRow);

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
