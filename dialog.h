#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include <QRect>
#include <QDesktopWidget>
#include <QProcess>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    void SetTime(int,int,int,int);
    bool isProcessExited(QString);

private slots:
    void UpdateTime();
    void on_radioButton_Hide_clicked();
    void on_pushButton_About_clicked();
};

#endif // DIALOG_H
