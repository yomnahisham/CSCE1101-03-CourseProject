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
    explicit GameOver(QWidget *parent = nullptr);
    ~GameOver();

private slots:
    void on_retryButton_clicked();

    void on_checkLevelsButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H
