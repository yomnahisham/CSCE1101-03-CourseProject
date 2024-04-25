#include "gameover.h"
#include "ui_gameover.h"
#include "windowmanager.h"

GameOver::GameOver(QWidget *parent, bool w)
    : QDialog(parent)
    , ui(new Ui::GameOver)
{
    ui->setupUi(this);

    if (!w)
    {
        ui -> wonLabel -> hide();
    }else if (w)
        ui -> wonLabel-> show();
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::on_retryButton_clicked()
{
    WindowManager Manager;
    Manager.showWindow(WindowManager::main);
    this->close();
}

void GameOver::on_checkLevelsButton_clicked()
{
    this->close();
    WindowManager Manager;
    Manager.showWindow(WindowManager::lev);
}

void GameOver::on_exitButton_clicked()
{
    qApp->quit(); //exit the whole app
}

void GameOver::on_leaderboardButton_clicked()
{
    // implement print of leaderboard to screen ui
}

