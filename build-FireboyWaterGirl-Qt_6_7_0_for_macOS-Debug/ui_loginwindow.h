/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QLabel *usernameLabel;
    QLabel *passLabel;
    QLineEdit *username_line;
    QLineEdit *pass_line;
    QLabel *usernameError;
    QLabel *passError;
    QPushButton *loginPush;
    QPushButton *registerPush;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(979, 838);
        usernameLabel = new QLabel(LoginWindow);
        usernameLabel->setObjectName("usernameLabel");
        usernameLabel->setGeometry(QRect(330, 360, 91, 16));
        passLabel = new QLabel(LoginWindow);
        passLabel->setObjectName("passLabel");
        passLabel->setGeometry(QRect(330, 390, 81, 16));
        username_line = new QLineEdit(LoginWindow);
        username_line->setObjectName("username_line");
        username_line->setGeometry(QRect(420, 360, 211, 21));
        pass_line = new QLineEdit(LoginWindow);
        pass_line->setObjectName("pass_line");
        pass_line->setGeometry(QRect(420, 390, 211, 21));
        pass_line->setEchoMode(QLineEdit::Password);
        usernameError = new QLabel(LoginWindow);
        usernameError->setObjectName("usernameError");
        usernameError->setGeometry(QRect(640, 360, 141, 21));
        passError = new QLabel(LoginWindow);
        passError->setObjectName("passError");
        passError->setGeometry(QRect(640, 390, 141, 21));
        loginPush = new QPushButton(LoginWindow);
        loginPush->setObjectName("loginPush");
        loginPush->setGeometry(QRect(390, 420, 100, 32));
        registerPush = new QPushButton(LoginWindow);
        registerPush->setObjectName("registerPush");
        registerPush->setGeometry(QRect(530, 420, 100, 32));

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Dialog", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginWindow", "Username:", nullptr));
        passLabel->setText(QCoreApplication::translate("LoginWindow", "Password:", nullptr));
        usernameError->setText(QCoreApplication::translate("LoginWindow", "*error username", nullptr));
        passError->setText(QCoreApplication::translate("LoginWindow", "*error pass", nullptr));
        loginPush->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        registerPush->setText(QCoreApplication::translate("LoginWindow", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
