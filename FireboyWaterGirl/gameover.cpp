#include "gameover.h"
#include "ui_gameover.h"
#include "windowmanager.h"

#include <QVBoxLayout>
#include <QPropertyAnimation>

GameOver::GameOver(QWidget *parent, int l, bool w,User* loggedUser)
    : QDialog(parent)
    , ui(new Ui::GameOver)
    , user(loggedUser)
{
    ui->setupUi(this);

    this -> l = l;
    qDebug()<< "game over created";
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
    // start level again
    WindowManager Manager;
    qDebug()<< "retrying";
    Manager.showWindow(WindowManager::main, l, user);
    this->close();
}

void GameOver::on_checkLevelsButton_clicked()
{
    // start level ui
    this->close();
    WindowManager Manager;
    Manager.showWindow(WindowManager::lev, 0, user);
}

void GameOver::on_exitButton_clicked()
{
    qApp->quit(); //exit the whole app
}


void GameOver::on_leaderboard_clicked()
{
    QDialog leaderboardDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(&leaderboardDialog);

    AllUsers allUsers;
    QVector<QPair<QString, int>> leaderboardData = allUsers.showLeaderboard();

    // find the highest score and its corresponding username
    int highestScore = 0;
    QString topPlayerUsername;
    for (const auto &pair : leaderboardData) {
        if (pair.second > highestScore) {
            highestScore = pair.second;
            topPlayerUsername = pair.first;
        }
    }

    for (int i = 0; i < leaderboardData.size(); ++i) {
        QString username = leaderboardData[i].first;
        int score = leaderboardData[i].second;

        QLabel* label = new QLabel(QString("<b>%1</b>: %2").arg(username).arg(score));
        label->setStyleSheet("QLabel { color: #333; font-size: 16px; margin-bottom: 10px; font-family: Times; }");

        layout->addSpacing(5);
        layout->addWidget(label);

        // highlight the top player with a style sheet animation
        if (username == topPlayerUsername) {
            QString styleSheet = "QLabel { color: #333; font-size: 16px; margin-bottom: 10px; font-family: Times; }";
            styleSheet += "QLabel:hover { color: #f00; }"; // hover effect
            label->setStyleSheet(styleSheet);
        }
    }

    leaderboardDialog.setStyleSheet("QDialog { background-color: #f7f7f7; border: 1px solid #ccc; border-radius: 10px; }");

    leaderboardDialog.exec();
}
