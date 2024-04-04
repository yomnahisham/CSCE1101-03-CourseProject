#ifndef FIREBOY_H
#define FIREBOY_H

#include "Players.h"
#include <QGraphicsPixmapItem>

class FireBoy : public Players, public QGraphicsPixmapItem, public QObject
{
    Q_OBJECT
public:
    FireBoy();
};

#endif // FIREBOY_H


