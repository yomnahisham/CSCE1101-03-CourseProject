#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QPixmap>
#include <QPalette>

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
