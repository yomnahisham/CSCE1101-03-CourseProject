#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "players.h"
#include<QObject>
#include<QGraphicsPixmapItem>
#include<QPixmap>

class Obstacles : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum ObstacleType{Side, Pavement,Slope,Ceiling, Fire, Water, Acid,tinyAcid, tinyWater, tinyFire, acidBall, openWD, openFD, FireDoor, WaterDoor, Block, Gem, Drops, LeverRight, LeverLeft, SlidingDoor, Button};
    Obstacles(QGraphicsItem* parent = nullptr);
    void createObstacle(ObstacleType type);
    void timerAcid();
    void moveAcid();
    void moveDoor(int x);

private:

};

#endif // OBSTACLES_H

//LeverRight, LeverLeft, Button1, Button2, SlidingFloor1, SlidingFloor2,
