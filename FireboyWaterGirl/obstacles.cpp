#include "obstacles.h"
#include "fireboy.h"
#include "watergirl.h"
#include "players.h"
#include<QTimer>
#include <QTransform>

// Pavement, Fire, Water, Acid, Lever, Button, SlidingFloor, FireDoor, WaterDoor

Obstacles::Obstacles(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
}

void Obstacles::createObstacle(ObstacleType type){
    //switch case for each obstacle that sets the object name (for collisions) and sets qpixmap

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
        setPixmap(QPixmap(":/image/img/fire.png").scaled(174, 45));
        break;
    case ObstacleType::Water:
        setObjectName("Water");
        setPixmap(QPixmap(":/image/img/water.png").scaled(174, 45));
        break;
    case ObstacleType::Acid:
        setObjectName("Acid");
        setPixmap(QPixmap(":/image/img/acid.png").scaled(170, 40));
        break;
    case ObstacleType::tinyAcid:
        setObjectName("Acid");
        setPixmap(QPixmap(":/image/img/tinyacid.png").scaled(70, 45, Qt::KeepAspectRatio));
        break;
    case ObstacleType::tinyWater:
        setObjectName("Water");
        setPixmap(QPixmap(":/image/img/Smallwater.png").scaled(70, 45, Qt::KeepAspectRatio));
        break;
    case ObstacleType::tinyFire:
        setObjectName("Fire");
        setPixmap(QPixmap(":/image/img/smallFire.png").scaled(70, 45, Qt::KeepAspectRatio));
        break;
    case ObstacleType::acidBall:
        setObjectName("Acid");
        setPixmap(QPixmap(":/image/img/acid ball.png").scaled(15, 15, Qt::KeepAspectRatio));
        timerAcid();    //call timer for acidbals whenever acid balls are created
        break;
    case ObstacleType::openWD:
        setObjectName("openWD");
        setPixmap(QPixmap(":/image/img/openWD.png").scaled(90, 105, Qt::KeepAspectRatio));
        break;
    case ObstacleType::openFD:
        setObjectName("openFD");
        setPixmap(QPixmap(":/image/img/openFD.png").scaled(80, 95, Qt::KeepAspectRatio));
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
        setPixmap(QPixmap(":/image/img/block.png").scaled(70,70, Qt::KeepAspectRatio));
        break;
    case ObstacleType::Gem:
        setObjectName("Gem");
        setPixmap(QPixmap(":/image/img/gems.png").scaled(30, 40, Qt::KeepAspectRatio));
        break;
    case ObstacleType::Drops:
        setObjectName("Drops");
        setPixmap(QPixmap(":/image/img/waterDrops.png").scaled(30, 40, Qt::KeepAspectRatio));
        break;
    case ObstacleType::LeverRight:
        setObjectName("LeverRight");
        setPixmap(QPixmap(":/image/img/lever.png").scaled(70, 57, Qt::KeepAspectRatio));
        break;
    case ObstacleType::LeverLeft:
        setObjectName("LeverLeft");
        setPixmap(QPixmap(":/image/img/LeverLeft.png").scaled(70, 57, Qt::KeepAspectRatio));
        break;
    }
}



void Obstacles::timerAcid()
{
    //use a Qtimer to call moveAcid every 40 ms
    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Obstacles::moveAcid);
    timer->start(40);
}

void Obstacles::moveAcid()
{

    setPos(x(),y()+5);  //moe it downwards

    bool hitPav = false;    //initalize hitpavement as false before checking

    //go through colliding items and make sure it isn't hitting pavement
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);
        if (ptr && ((ptr->objectName() == "Pavement")||(ptr->objectName() == "Block"))) {
            hitPav = true;} //if it hit pavement set boolean to true
    }

    if (hitPav)
    {
        scene()->removeItem(this);  //remove drop from scene
        delete this;                //delete object
    }
}

/*    case ObstacleType::LeverRight:
        setObjectName("LeverRight");
        setPixmap(QPixmap(":/image/img/lever.png").scaled(70, 57, Qt::KeepAspectRatio));
        break;
        case ObstacleType::LeverLeft:
        setObjectName("LeverLeft");
        setPixmap(QPixmap(":/image/img/LeverLeft.png").scaled(70, 57, Qt::KeepAspectRatio));
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
        break;*/

