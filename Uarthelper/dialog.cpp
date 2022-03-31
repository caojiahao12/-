#include "dialog.h"
#include "ui_dialog.h"
#include<QSerialPortInfo>
#include<QList>
#include<QtDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    misopen = false;
    ui->BtnSend->setEnabled(misopen);
    //识别串口号
    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();
    int count = serialPortInfo.count();
    for (int i = 0; i < count; i++)
    {
      ui->CBoxSerialPort->addItem(serialPortInfo.at(i).portName()) ;
    }
    // connect(&mSerialPort, SIGNAL(redyRead()),this,SLOT();
    connect(&mSerialPort,SIGNAL(readyRead()),this,SLOT(on_SerialPort_readyRead()));

}

Dialog::~Dialog()
{
    delete ui;

}

bool Dialog::getSerialPortConfig()
{
    //获取串口配置
     mPortName = ui->CBoxSerialPort->currentText();
     mBaudRate = ui->CBoxBaudrate->currentText();
     mParity = ui->CBoxParity->currentText();
     mDataBits = ui->CBoxDataBits->currentText();
     mStopBits = ui->CBoxStopBits->currentText();
     //设置串口配置
     mSerialPort.setPortName(mPortName);
     if("9600" == mBaudRate)
     {
         mSerialPort.setBaudRate(QSerialPort::Baud9600);
     }
     else if("19200" == mBaudRate)
     {
         mSerialPort.setBaudRate(QSerialPort::Baud19200);
     }
     else
     {
         mSerialPort.setBaudRate(QSerialPort::Baud115200);
     }

     if("EVEN" == mParity)
     {
         mSerialPort.setParity(QSerialPort::EvenParity);
     }
     else if("ODD" == mParity)
     {
         mSerialPort.setParity(QSerialPort::OddParity);
     }
     else
     {
       mSerialPort.setParity(QSerialPort::NoParity);
     }
     if("5" == mDataBits)
     {
         mSerialPort.setDataBits(QSerialPort::Data5);
     }
     else if ("6" == mDataBits)
     {
       mSerialPort.setDataBits(QSerialPort::Data6);
     }
     else if ("7" == mDataBits)
     {
       mSerialPort.setDataBits(QSerialPort::Data7);
     }
     else
     {
          mSerialPort.setDataBits(QSerialPort::Data8);
     }
     if("1.5" == mStopBits)
     {
         mSerialPort.setStopBits(QSerialPort::OneAndHalfStop);
     }
     else if("1.5" == mStopBits)
     {
         mSerialPort.setStopBits(QSerialPort::OneAndHalfStop);
     }
     if("2" == mStopBits)
     {
         mSerialPort.setStopBits(QSerialPort::TwoStop);
     }
     else
     {
         mSerialPort.setStopBits(QSerialPort::OneStop);
     }
     return mSerialPort.open(QSerialPort::ReadWrite);

}

void Dialog::on_BtnOpen_clicked()
{
  if(true == misopen)
  {
      mSerialPort.close();
      ui->BtnOpen->setText("打开");
      misopen = false;
      ui->BtnSend->setEnabled(misopen);
      ui->CBoxSerialPort->setEnabled(true);
      ui->CBoxBaudrate->setEnabled(true);
      ui->CBoxParity->setEnabled(true);
      ui->CBoxDataBits->setEnabled(true);
      ui->CBoxStopBits->setEnabled(true);
  }
  else
  {


   if(true == getSerialPortConfig())
   {
     misopen = true;
     ui->BtnOpen->setText("关闭");
     qDebug() <<"成功打开串口" <<mPortName;
     ui->BtnSend->setEnabled(misopen);
     ui->CBoxSerialPort->setEnabled(false);
     ui->CBoxBaudrate->setEnabled(false);
     ui->CBoxParity->setEnabled(false);
     ui->CBoxDataBits->setEnabled(false);
     ui->CBoxStopBits->setEnabled(false);

   }
//   else
//   {
//     misopen = false;
//   }
  }
}

void Dialog::on_BtnSend_clicked()
{
    if( misopen == true)
    {
        mSerialPort.write(ui->TeditSend->toPlainText().toStdString().c_str());
    }
}

void Dialog::on_SerialPort_readyRead()
{
    if( misopen == true)
    {
      QByteArray recvData = mSerialPort.readAll();
      ui->TditRecv->append(QString(recvData));
    }
}


