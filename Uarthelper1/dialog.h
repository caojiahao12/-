#ifndef DIALOG_H
#define DIALOG_H
#include<QSerialPort>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:


    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
     bool getSerialPortConfig(void);

private slots:
    void on_BtnOpen_clicked();

    void on_BtnSend_clicked();
    void on_SerialPort_readyRead();

private:
    Ui::Dialog *ui;
    QSerialPort mSerialPort;
    bool misopen;
    QString mPortName;
    QString mBaudRate;
    QString mParity;
    QString mDataBits;
    QString mStopBits;
};

#endif // DIALOG_H
