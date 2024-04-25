#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "players.h"
#include<QObject>
#include<QGraphicsPixmapItem>
#include<QPixmap>

class Obstacles : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum ObstacleType{Side, Pavement,Slope,Ceiling, Fire, Water, Acid, LeverRight, LeverLeft, Button1, Button2, SlidingFloor1, SlidingFloor2, FireDoor, WaterDoor, Block};
    Obstacles(QGraphicsItem* parent = nullptr);
    void createObstacle(ObstacleType type);
    void lowerFloor();
private:
    ObstacleType getType()const;
    ObstacleType type;

};

#endif // OBSTACLES_H
