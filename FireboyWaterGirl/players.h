#ifndef PLAYERS_H
#define PLAYERS_H

#include <QMainWindow>

class Players : public QMainWindow
{
    Q_OBJECT

public:
    Players(QWidget *parent = nullptr);
    ~Players();
};
#endif // PLAYERS_H
