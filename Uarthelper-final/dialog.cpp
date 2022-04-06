#include "dialog.h"
#include "ui_dialog.h"
#include<QSerialPortInfo>
#include<QList>
#include<QtDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)

{
    this->setObjectName("dialog");
    this->setStyleSheet("QDialog#dialog{border-image:url(ny.jpg)}");
    ui->setupUi(this);
    misopen = false;
    ui->pushButton_motor->setEnabled(misopen);
    //识别串口号
    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();
    int count = serialPortInfo.count();
    for (int i = 0; i < count; i++)
    {
      ui->CBoxSerialPort->addItem(serialPortInfo.at(i).portName()) ;
    }

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
         mSerialPort.setParity(QSerialPort::NoParity);

         mSerialPort.setDataBits(QSerialPort::Data8);

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
      ui->pushButton_motor->setEnabled(misopen);
      ui->CBoxSerialPort->setEnabled(true);
      ui->CBoxBaudrate->setEnabled(true);

  }
  else
  {


   if(true == getSerialPortConfig())
   {
     misopen = true;
     ui->BtnOpen->setText("关闭");
     qDebug() <<"成功打开串口" <<mPortName;
     ui->pushButton_motor->setEnabled(misopen);
     ui->CBoxSerialPort->setEnabled(false);
     ui->CBoxBaudrate->setEnabled(false);


   }

  }
}
void Dialog::on_SerialPort_readyRead()
{
    bool ok = true;

    //注意data在.h中进行定义，应为需要全局使用
    if(data.size()!=18)//收不够18个字符，就在槽函数中不断累积
    {
        data.append(mSerialPort.readAll());
    }
    if(data.size()==18)//攒够18个字符，进行一次处理
    {
        if(data.mid(0,4)=="COMM")//mid(0,4)表示从data的第0位开始取4个字符
        {
            //toInt转变为整数再number变为string是为了去掉前边的0
            ui->lineEdit_tem->setText(QString::number(data.midRef(4,4).toInt(&ok)));
            ui->lineEdit_hum->setText(QString::number(data.midRef(8,4).toInt(&ok)));
            ui->lineEdit_lum->setText(QString::number(data.midRef(12,4).toInt(&ok)));
            if(data.mid(16,1)=='0')
            {
                ui->Button_light->setText(QString("OFF"));
            }
            else
            {
                ui->Button_light->setText(QString("ON"));
            }

            if(data.mid(17,1)=='0')
                ui->Button_motor ->setText(QString("OFF"));
            else
                ui->Button_motor->setText(QString("ON"));

            mSerialPort.clear();
            data.clear();//够16个字符，做一次清除，不影响后续数据接收
        }
    }
}






void Dialog::on_pushButton_motor_clicked()
{
    mSerialPort.write("M");
    if(ui->Button_motor->text() == "ON")
        ui->Button_motor->setText("OFF");
    else
        ui->Button_motor->setText("ON");
}

void Dialog::on_pushButton_light_clicked()
{
    mSerialPort.write("L");
    if(ui->Button_light->text() == "ON")
        ui->Button_light->setText("OFF");
    else
        ui->Button_light->setText("ON");


}
