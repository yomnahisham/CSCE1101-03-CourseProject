#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "players.h"
#include<QObject>
#include<QGraphicsPixmapItem>
#include<QPixmap>

class Obstacles : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum ObstacleType{Side, Pavement,Slope,Ceiling, Fire, Water, Acid,tinyAcid, acidBall, openWD, openFD, FireDoor, WaterDoor, Block, Gem, Drops, LeverRight, LeverLeft};
    Obstacles(QGraphicsItem* parent = nullptr);
    void createObstacle(ObstacleType type);
    void lowerFloor();
    void elevateFloor(Players* player);
    void timerAcid();
    void moveAcid();


private:
    ObstacleType getType()const;
    ObstacleType type;

};

#endif // OBSTACLES_H

//LeverRight, LeverLeft, Button1, Button2, SlidingFloor1, SlidingFloor2,
