#include "gameover.h"
#include "ui_gameover.h"

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

}

void GameOver::on_leaderboardButton_clicked()
{

}

void GameOver::on_checkLevelsButton_clicked()
{

}

void GameOver::on_exitButton_clicked()
{

}

