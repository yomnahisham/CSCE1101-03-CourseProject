#include "gameover.h"
#include "ui_gameover.h"
#include "windowmanager.h"

GameOver::GameOver(QWidget *parent, int l, bool w,User* loggedUser, AllUsers* Allusers)
    : QDialog(parent)
    , ui(new Ui::GameOver)
    , user(loggedUser)
    ,allusers(Allusers)
{
    ui->setupUi(this);

    this -> l = l;

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
    Manager.showWindow(WindowManager::main, l, user, allusers);
    this->close();
}

void GameOver::on_checkLevelsButton_clicked()
{
    this->close();
    WindowManager Manager;
    Manager.showWindow(WindowManager::lev, 0, user, allusers);
}

void GameOver::on_exitButton_clicked()
{
    qApp->quit(); //exit the whole app
}

void GameOver::on_leaderboardButton_clicked()
{
    // implement print of leaderboard to screen ui
}

