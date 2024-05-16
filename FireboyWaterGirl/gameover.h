#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>

namespace Ui {
class GameOver;
}

class GameOver : public QDialog
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = nullptr, int l = 0, bool w = false);
    ~GameOver();

private slots:
    void on_retryButton_clicked();

    void on_checkLevelsButton_clicked();

    void on_exitButton_clicked();

    void on_leaderboardButton_clicked();

private:
    Ui::GameOver *ui;
    int l;
};

#endif // GAMEOVER_H
