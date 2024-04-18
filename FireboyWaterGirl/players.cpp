#include "players.h"
#include "obstacles.h"
#include "watergirl.h"
#include "fireboy.h"
#include <QTimer>


Players::Players(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {}

void Players::gravity ()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if ((typeid(*(colliding_items[i])) == (typeid (Obstacles)) || (typeid(*(colliding_items[i])) == typeid(WaterGirl))|| (typeid(*(colliding_items[i])) == typeid(FireBoy))))//note this is all obstacles (can't pass through them)
        {
            setPos(x(), y());
            /*if (direction == 1){             // need to deffrentiate between side collision and bottom and top collision
                right = false;
                left = true;
            }else if (direction == 2){
                left = false;
                right = true;
            }*/
            qDebug()<<"water girl is touching pavement";
            return;
        }
        else
        {
            qDebug()<<"water girl is in the air";
            moveBy (0,2);
            QTimer::singleShot(20, this, [this]() { gravity(); });
        }
    }
}

//Players::~Players() {}


