#ifndef OBSTACLES_H
#define OBSTACLES_H

#include<QObject>
#include<QGraphicsPixmapItem>
#include<QPixamp>
class Obstacles : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum ObstacleType{Pavement, Fire, Water, Acid, Lever, Button, SlidingFloor, FireDoor, WaterDoor};
    Obstacles();
};

#endif // OBSTACLES_H
