#ifndef LEVEL_H
#define LEVEL_H

#include "user.h"
#include <QDialog>

namespace Ui {
class Level;
}

class Level : public QDialog
{
    Q_OBJECT

public:
    explicit Level(QWidget *parent = nullptr, User* loggeduser = nullptr);
    ~Level();

private slots:
    void on_Level1_clicked();

    void on_level2B_clicked();

    void on_level3B_clicked();

    void on_level4B_clicked();

    void on_level5B_clicked();

private:
    User* user;
    Ui::Level *ui;
};

#endif // LEVEL_H
