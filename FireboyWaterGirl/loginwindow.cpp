#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "allusers.h"
#include "registerwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QString>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    ui->usernameError->setVisible(false);
    ui->passError->setVisible(false);
    ui->usernameError->setStyleSheet("QLabel { color : red; }");
    ui->passError->setStyleSheet("QLabel { color : red; }");
    ui->usernameLabel->setStyleSheet("QLabel { color : white; }");
    ui->passLabel->setStyleSheet("QLabel { color : white; }");

    QPixmap background(":/image/img/TempleHallForest.png");
    background = background.scaled(this->size(), Qt::KeepAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginPush_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    bool found = false;
    for (int i = 0; i < usersCount; ++i) {
        if (usernames[i] == username && passwords[i] == password) {
            found = true;
            int userAge = ages[i];
            hide();
            WelcomeWindow *welcomeWindow = new WelcomeWindow(username, nullptr);
            welcomeWindow->show();
            break;
        }
    }

    if (!found) {
        ui->label_error->setStyleSheet("QLabel { color : red; }");
        ui->label_error->setText("Wrong username or password!");
        ui->label_error->setVisible(true);
    }
}


void LoginWindow::on_registerPush_clicked()
{
    hide();
    RegisterWindow *registerWindow = new RegisterWindow(nullptr);
    registerWindow->show();
}

