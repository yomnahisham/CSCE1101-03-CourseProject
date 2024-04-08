#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QPixmap>
#include <QPalette>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

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
