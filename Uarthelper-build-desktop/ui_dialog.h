/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Tue Oct 24 16:54:03 2023
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *BtnOpen;
    QPushButton *pushButton_motor;
    QPushButton *pushButton_light;
    QLabel *label;
    QComboBox *CBoxSerialPort;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_tem;
    QLineEdit *lineEdit_tem;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_hum;
    QLineEdit *lineEdit_hum;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_lum;
    QLineEdit *lineEdit_lum;
    QLabel *label_2;
    QComboBox *CBoxBaudrate;
    QPushButton *Button_light;
    QPushButton *Button_motor;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(704, 582);
        Dialog->setStyleSheet(QString::fromUtf8("background-image: url(:/icon/ny.jpg);"));
        BtnOpen = new QPushButton(Dialog);
        BtnOpen->setObjectName(QString::fromUtf8("BtnOpen"));
        BtnOpen->setGeometry(QRect(500, 110, 111, 101));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Black"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        BtnOpen->setFont(font);
        BtnOpen->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: rgb(0, 0, 0);\n"
"	background-image: url(:/icon/R-C.jfif);\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"	color: rgb(255, 255, 255);\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgb(122, 211, 140), stop:1 rgb(59, 195, 129));\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	border: 2px solid qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgb(122, 211, 140), stop:1 rgb(59, 195, 129));\n"
"	color: qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgb(122, 211, 140), stop:1 rgb(59, 195, 129));\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"	border: 2px solid qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgb(122, 211, 140), stop:1 rgb(59, 195, 129));\n"
"	color: rgb(153, 153, 153);\n"
"	background-color: rgb(212, 228, 235);\n"
"}"));
        pushButton_motor = new QPushButton(Dialog);
        pushButton_motor->setObjectName(QString::fromUtf8("pushButton_motor"));
        pushButton_motor->setGeometry(QRect(450, 440, 91, 41));
        pushButton_motor->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);\n"
"font: 75 italic 12pt \"Bahnschrift\";\n"
"color: rgb(255, 255, 0);\n"
""));
        pushButton_light = new QPushButton(Dialog);
        pushButton_light->setObjectName(QString::fromUtf8("pushButton_light"));
        pushButton_light->setGeometry(QRect(70, 440, 91, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bahnschrift"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(true);
        font1.setWeight(9);
        pushButton_light->setFont(font1);
        pushButton_light->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);\n"
"color: rgb(255, 255, 0);\n"
"font: 75 italic 12pt \"Bahnschrift\";\n"
""));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 110, 81, 41));
        CBoxSerialPort = new QComboBox(Dialog);
        CBoxSerialPort->setObjectName(QString::fromUtf8("CBoxSerialPort"));
        CBoxSerialPort->setGeometry(QRect(230, 110, 251, 41));
        CBoxSerialPort->setStyleSheet(QString::fromUtf8("font: 87 10pt \"Arial Black\";"));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(200, 240, 251, 161));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_tem = new QLabel(layoutWidget);
        label_tem->setObjectName(QString::fromUtf8("label_tem"));

        horizontalLayout_3->addWidget(label_tem);

        lineEdit_tem = new QLineEdit(layoutWidget);
        lineEdit_tem->setObjectName(QString::fromUtf8("lineEdit_tem"));
        lineEdit_tem->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 12pt \"Arial\";\n"
"font: 16pt \"Arial\";\n"
"font: 14pt \"Arial\";\n"
"color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(255, 255, 255);\n"
"selection-color: rgb(255, 0, 0);"));
        lineEdit_tem->setAlignment(Qt::AlignCenter);
        lineEdit_tem->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_tem);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);

        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_hum = new QLabel(layoutWidget);
        label_hum->setObjectName(QString::fromUtf8("label_hum"));

        horizontalLayout_4->addWidget(label_hum);

        lineEdit_hum = new QLineEdit(layoutWidget);
        lineEdit_hum->setObjectName(QString::fromUtf8("lineEdit_hum"));
        lineEdit_hum->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 12pt \"Arial\";\n"
"font: 16pt \"Arial\";\n"
"color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(255, 255, 255);\n"
"selection-color: rgb(255, 0, 0);"));
        lineEdit_hum->setAlignment(Qt::AlignCenter);
        lineEdit_hum->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEdit_hum);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 3);

        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_lum = new QLabel(layoutWidget);
        label_lum->setObjectName(QString::fromUtf8("label_lum"));

        horizontalLayout_5->addWidget(label_lum);

        lineEdit_lum = new QLineEdit(layoutWidget);
        lineEdit_lum->setObjectName(QString::fromUtf8("lineEdit_lum"));
        lineEdit_lum->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 12pt \"Arial\";\n"
"font: 16pt \"Arial\";\n"
"color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(255, 255, 255);\n"
"selection-color: rgb(255, 0, 0);"));
        lineEdit_lum->setAlignment(Qt::AlignCenter);
        lineEdit_lum->setReadOnly(true);
        lineEdit_lum->setClearButtonEnabled(false);

        horizontalLayout_5->addWidget(lineEdit_lum);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 3);

        verticalLayout_2->addLayout(horizontalLayout_5);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 167, 81, 41));
        CBoxBaudrate = new QComboBox(Dialog);
        CBoxBaudrate->setObjectName(QString::fromUtf8("CBoxBaudrate"));
        CBoxBaudrate->setGeometry(QRect(230, 170, 251, 41));
        CBoxBaudrate->setStyleSheet(QString::fromUtf8("font: 87 10pt \"Arial Black\";"));
        Button_light = new QPushButton(Dialog);
        Button_light->setObjectName(QString::fromUtf8("Button_light"));
        Button_light->setGeometry(QRect(161, 440, 91, 41));
        Button_light->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"image: url(:/icon/R-C (1).jfif);\n"
"font: 87 10pt \"Arial Black\";"));
        Button_motor = new QPushButton(Dialog);
        Button_motor->setObjectName(QString::fromUtf8("Button_motor"));
        Button_motor->setGeometry(QRect(540, 440, 91, 41));
        Button_motor->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"image: url(:/icon/R-C (1).jfif);\n"
"font: 87 10pt \"Arial Black\";"));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\346\231\272\346\205\247\345\206\234\344\270\232\345\212\251\346\211\213", 0, QApplication::UnicodeUTF8));
        BtnOpen->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        pushButton_motor->setText(QApplication::translate("Dialog", "\351\251\254\350\276\276", 0, QApplication::UnicodeUTF8));
        pushButton_light->setText(QApplication::translate("Dialog", "\347\201\257", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ffff00;\">\344\270\262\345\217\243\345\217\267</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_tem->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:8pt; font-weight:600; color:#00ff00;\">\346\270\251\345\272\246</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_hum->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:8pt; font-weight:600; color:#55ff00;\">\346\271\277\345\272\246</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_lum->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:8pt; font-weight:600; color:#55ff00;\">\345\205\211\347\205\247</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600; color:#ffff00;\">\346\263\242\347\211\271\347\216\207</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        CBoxBaudrate->clear();
        CBoxBaudrate->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "115200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "9600", 0, QApplication::UnicodeUTF8)
        );
        Button_light->setText(QString());
        Button_motor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
