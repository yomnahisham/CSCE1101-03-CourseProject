#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerwindow.h"
#include "user.h"
#include "allusers.h"
#include <main.cpp>
#include <QPixmap>
#include <QPalette>
#include <QString>

LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent), ui(new Ui::LoginWindow){
    ui->setupUi(this);

    qDebug()<<QSqlDatabase::drivers();

    ui->usernameError->setVisible(false);
    ui->usernameError->setStyleSheet("QLabel { color : red; }");

    ui->passError->setVisible(false);
    ui->passError->setStyleSheet("QLabel { color : red; }");

    ui->usernameLabel->setStyleSheet("QLabel { color : white; }");
    ui->passLabel->setStyleSheet("QLabel { color : white; }");

    QPixmap background(":/image/img/LoginWindow.png");
    background = background.scaled(this->size(), Qt::KeepAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

}

LoginWindow::~LoginWindow(){
    delete ui;
}

void LoginWindow::on_loginPush_clicked(){
    QString username = ui->username_line->text();
    QString password = ui->pass_line->text();
    bool userTrue = AllUsers::authenticateUser(username, password);
    if (userTrue){
        WindowManager window;
        window.showWindow(WindowManager::lev);
        hide();
    }else{
        ui->usernameError->setVisible(true);
        ui->passError->setVisible(true);
    }
}


void LoginWindow::on_registerPush_clicked(){
    WindowManager Manager;
    Manager.showWindow(WindowManager::reg);
    hide();
}

