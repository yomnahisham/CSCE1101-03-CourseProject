#ifndef OBSTACLES_H
#define OBSTACLES_H

#include<QObject>
#include<QGraphicsPixmapItem>
#include<QPixmap>

class Obstacles : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enum ObstacleType{Pavement, Fire, Water, Acid, Lever, Button, SlidingFloor, FireDoor, WaterDoor};
    Obstacles(ObstacleType type);
private:
    ObstacleType type;
};

#endif // OBSTACLES_H
