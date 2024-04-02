#include "players.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

Players::Players(QWidget *parent) : QMainWindow(parent)
{
    QGraphicsRectItem* Fire = new QGraphicsRectItem(0, 0, 50, 70);

    Fire->scene();
}

Players::~Players() {}
