/********************************************************************************
** Form generated from reading UI file 'registerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWINDOW_H
#define UI_REGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RegisterWindow
{
public:
    QLabel *userlabel;
    QLabel *passlabel;
    QLabel *repeatlabel;
    QPushButton *regButton;
    QLineEdit *userline;
    QLineEdit *passline;
    QLineEdit *repeatline;
    QLabel *usererror;
    QLabel *passerror;

    void setupUi(QDialog *RegisterWindow)
    {
        if (RegisterWindow->objectName().isEmpty())
            RegisterWindow->setObjectName("RegisterWindow");
        RegisterWindow->resize(459, 282);
        userlabel = new QLabel(RegisterWindow);
        userlabel->setObjectName("userlabel");
        userlabel->setGeometry(QRect(60, 80, 91, 16));
        passlabel = new QLabel(RegisterWindow);
        passlabel->setObjectName("passlabel");
        passlabel->setGeometry(QRect(60, 110, 71, 20));
        repeatlabel = new QLabel(RegisterWindow);
        repeatlabel->setObjectName("repeatlabel");
        repeatlabel->setGeometry(QRect(20, 140, 111, 20));
        regButton = new QPushButton(RegisterWindow);
        regButton->setObjectName("regButton");
        regButton->setGeometry(QRect(170, 190, 100, 32));
        userline = new QLineEdit(RegisterWindow);
        userline->setObjectName("userline");
        userline->setGeometry(QRect(160, 80, 113, 21));
        passline = new QLineEdit(RegisterWindow);
        passline->setObjectName("passline");
        passline->setGeometry(QRect(160, 110, 113, 21));
        passline->setEchoMode(QLineEdit::Password);
        repeatline = new QLineEdit(RegisterWindow);
        repeatline->setObjectName("repeatline");
        repeatline->setGeometry(QRect(160, 140, 113, 21));
        repeatline->setEchoMode(QLineEdit::Password);
        usererror = new QLabel(RegisterWindow);
        usererror->setObjectName("usererror");
        usererror->setGeometry(QRect(300, 80, 161, 16));
        passerror = new QLabel(RegisterWindow);
        passerror->setObjectName("passerror");
        passerror->setGeometry(QRect(300, 140, 161, 16));

        retranslateUi(RegisterWindow);

        QMetaObject::connectSlotsByName(RegisterWindow);
    } // setupUi

    void retranslateUi(QDialog *RegisterWindow)
    {
        RegisterWindow->setWindowTitle(QCoreApplication::translate("RegisterWindow", "Dialog", nullptr));
        userlabel->setText(QCoreApplication::translate("RegisterWindow", "Username: ", nullptr));
        passlabel->setText(QCoreApplication::translate("RegisterWindow", "Password: ", nullptr));
        repeatlabel->setText(QCoreApplication::translate("RegisterWindow", "Repeat Password:", nullptr));
        regButton->setText(QCoreApplication::translate("RegisterWindow", "Register", nullptr));
        usererror->setText(QCoreApplication::translate("RegisterWindow", "<html><head/><body><p><span style=\" color:#941100;\">username already in use</span></p></body></html>", nullptr));
        passerror->setText(QCoreApplication::translate("RegisterWindow", "<html><head/><body><p><span style=\" color:#941100;\">password incorrect</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWindow: public Ui_RegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWINDOW_H
