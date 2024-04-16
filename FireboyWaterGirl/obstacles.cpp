#include "obstacles.h"

// Pavement, Fire, Water, Acid, Lever, Button, SlidingFloor, FireDoor, WaterDoor

Obstacles::Obstacles(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
}

void Obstacles::createObstacle(ObstacleType type){
    switch (type) {
    case ObstacleType::Pavement: // no image for pavement
        setPixmap(QPixmap(":/image/img/watergirl.png").scaled(100, 100));
        break;
    case ObstacleType::Fire:
        setPixmap(QPixmap(":/image/img/fire.png").scaled(100, 100));
        break;
    case ObstacleType::Water:
        setPixmap(QPixmap(":/image/img/water.png").scaled(100, 100));
        break;
    case ObstacleType::Acid:
        setPixmap(QPixmap(":/image/img/acid.png").scaled(100, 100));
        break;
    case ObstacleType::Lever:
        setPixmap(QPixmap(":/image/img/lever.png").scaled(100, 100));
        break;
    case ObstacleType::Button1:
        setPixmap(QPixmap(":/image/img/pushButton1.png").scaled(100, 100));
        break;
    case ObstacleType::Button2:
        setPixmap(QPixmap("qrc:/image/img/pushButton2.png").scaled(100, 100));
        break;
    case ObstacleType::SlidingFloor1:
        setPixmap(QPixmap(":/image/img/slidingFloor.png").scaled(100, 100));
        break;
    case ObstacleType::SlidingFloor2:
        setPixmap(QPixmap(":/image/img/slidingFloor2.png").scaled(100, 100));
        break;
    case ObstacleType::FireDoor:
        setPixmap(QPixmap(":/image/img/fireDoor.png").scaled(100, 100));
        break;
    case ObstacleType::WaterDoor:
        setPixmap(QPixmap(":/image/img/WaterDoor.png").scaled(100, 100));
        break;
    }
}
