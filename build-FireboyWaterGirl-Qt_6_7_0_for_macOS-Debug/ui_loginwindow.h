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

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QLabel *usernameLabel;
    QLabel *passLabel;
    QLineEdit *username_line;
    QLineEdit *pass_line;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(979, 838);
        usernameLabel = new QLabel(LoginWindow);
        usernameLabel->setObjectName("usernameLabel");
        usernameLabel->setGeometry(QRect(260, 400, 91, 16));
        passLabel = new QLabel(LoginWindow);
        passLabel->setObjectName("passLabel");
        passLabel->setGeometry(QRect(260, 430, 81, 16));
        username_line = new QLineEdit(LoginWindow);
        username_line->setObjectName("username_line");
        username_line->setGeometry(QRect(350, 400, 211, 21));
        pass_line = new QLineEdit(LoginWindow);
        pass_line->setObjectName("pass_line");
        pass_line->setGeometry(QRect(350, 430, 211, 21));
        label = new QLabel(LoginWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(570, 400, 141, 21));
        label_2 = new QLabel(LoginWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(570, 430, 141, 21));

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Dialog", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginWindow", "Username:", nullptr));
        passLabel->setText(QCoreApplication::translate("LoginWindow", "Password:", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "*error username", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "*error pass", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
