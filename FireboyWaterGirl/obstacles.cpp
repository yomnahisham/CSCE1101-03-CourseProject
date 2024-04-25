#include "obstacles.h"
#include "fireboy.h"
#include "watergirl.h"
#include "players.h"
#include<QTimer>

// Pavement, Fire, Water, Acid, Lever, Button, SlidingFloor, FireDoor, WaterDoor

Obstacles::Obstacles(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
}

void Obstacles::createObstacle(ObstacleType type){
    switch (type) {
    case ObstacleType::Pavement:
        setObjectName("Pavement");
        break;
    case ObstacleType::Side:
        setObjectName("Side");
        break;
    case ObstacleType::Slope:
        setObjectName("Slope");
        break;
    case ObstacleType::Ceiling:
        setObjectName("Ceiling");
        break;
    case ObstacleType::Fire:
        setObjectName("Fire");
        setPixmap(QPixmap(":/image/img/fire.png").scaled(174, 45)); //multiply pixels by a factor to get proper size
        break;
    case ObstacleType::Water:
        setObjectName("Water");
        setPixmap(QPixmap(":/image/img/water.png").scaled(174, 45));
        break;
    case ObstacleType::Acid:
        setObjectName("Acid");
        setPixmap(QPixmap(":/image/img/acid.png").scaled(170, 40));
        break;
    case ObstacleType::LeverRight:
        setObjectName("LeverRight");
        setPixmap(QPixmap(":/image/img/lever.png").scaled(66, 57, Qt::KeepAspectRatio));
        break;
        case ObstacleType::LeverLeft:
        setObjectName("LeverLeft");
        setPixmap(QPixmap(":/image/img/LeverLeft.png").scaled(66, 57, Qt::KeepAspectRatio));
        break;
    case ObstacleType::Button1:
        setObjectName("Button1");
        setPixmap(QPixmap(":/image/img/pushButton1.png").scaled(50, 24, Qt::KeepAspectRatio));
        break;
    case ObstacleType::Button2:
        setObjectName("Button2");
        setPixmap(QPixmap(":/image/img/pushButton2.png").scaled(50, 24, Qt::KeepAspectRatio));
        break;
    case ObstacleType::SlidingFloor1:
        setObjectName("SlidingFloor1");
        setPixmap(QPixmap(":/image/img/slidingFloor.png").scaled(110, 34, Qt::KeepAspectRatio));
        break;
    case ObstacleType::SlidingFloor2:
        setObjectName("SlidingFloor2");
        setPixmap(QPixmap(":/image/img/slidingFloor2.png").scaled(110, 34, Qt::KeepAspectRatio));
        break;
    case ObstacleType::FireDoor:
        setObjectName("FireDoor");
        setPixmap(QPixmap(":/image/img/fireDoor.png").scaled(80, 95, Qt::KeepAspectRatio));
        break;
    case ObstacleType::WaterDoor:
        setObjectName("WaterDoor");
        setPixmap(QPixmap(":/image/img/WaterDoor.png").scaled(90, 105, Qt::KeepAspectRatio));
        break;
    case ObstacleType::Block:
        setObjectName("Block");
        setPixmap(QPixmap(":/image/img/block.png").scaled (50,50,Qt::KeepAspectRatio));
        break;
    }
}

void Obstacles::lowerFloor(){
    qDebug()<< "entered func";

    while (y() < 528)
    {
        moveBy(0, 3);
        QTimer::singleShot(40, this, [this]() { lowerFloor(); });
    }
    return;
}


