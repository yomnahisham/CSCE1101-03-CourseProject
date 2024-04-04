#ifndef PLAYERS_H
#define PLAYERS_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

class Players : public QMainWindow, public QGraphicsPixmapItem, public QObject
{
    Q_OBJECT

public:
    Players(QWidget *parent = nullptr);
    ~Players();
};
#endif // PLAYERS_H
