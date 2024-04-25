#include "gameover.h"
#include "ui_gameover.h"
#include "windowmanager.h"

GameOver::GameOver(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameOver)
{
    ui->setupUi(this);
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::on_retryButton_clicked()
{
    this->close();
    WindowManager Manager;
    Manager.showWindow(WindowManager::main);
}

void GameOver::on_checkLevelsButton_clicked()
{
    this->close();
    WindowManager Manager;
    Manager.showWindow(WindowManager::lev);
}

void GameOver::on_exitButton_clicked()
{
    qApp->quit();
}

void GameOver::on_leaderboardButton_clicked()
{

}

