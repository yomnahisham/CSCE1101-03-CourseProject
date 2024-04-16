#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "user.h"
#include "allusers.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui-> passerror -> hide();
    ui-> usererror -> hide();

    ui->userlabel->setStyleSheet("QLabel { color : white; }");
    ui->passlabel->setStyleSheet("QLabel { color : white; }");
    ui->repeatlabel->setStyleSheet("QLabel { color : white; }");

    QPixmap background(":/image/img/registerBackground.png");             //change it later to make it different from login
    background = background.scaled(this->size(), Qt::KeepAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_regButton_clicked()
{   //check for same username
    bool userExists = false;
    QString inputUsername = ui->userline->text();
    userExists = AllUsers::search(inputUsername);

    if (userExists){
        ui->usererror->setText("Username already exists.");
        ui->usererror->setVisible(true);
    }

    //check password and repeat is the same
    QString inputPassword;

    bool passMatchs = false;
    QString firstPass = ui->passline->text();
    QString secondPass = ui->repeatline->text();
    if (firstPass == secondPass) {
        inputPassword = ui-> passline -> text();
        passMatchs = true;
    } else {
        ui->passerror->setText("Password does not match.");
        ui -> passerror -> show();
    }

    //add user to allusers database
    if (passMatchs && userExists){
        User::newUser(inputUsername, inputPassword);
        this->hide();
    }
}


void RegisterWindow::on_pushButton_clicked()
{
    this->hide();
    // call a function to change the window showing
}

