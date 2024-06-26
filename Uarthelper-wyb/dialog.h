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

    void on_pushButton_motor_clicked();

    void on_pushButton_light_clicked();

private:
    Ui::Dialog *ui;
    QSerialPort mSerialPort;
    bool misopen;
    QString mPortName;
    QString mBaudRate;
    QString mParity;
    QString mDataBits;
    int data_process(char *data,int i);
    QString mStopBits;
    QString data;

};

#endif // DIALOG_H
