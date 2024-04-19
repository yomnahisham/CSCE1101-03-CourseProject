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
        const std::type_info& type = typeid(*(colliding_items[i]));
        if (QGraphicsItem* obs = (colliding_items[i]))
        {
            qDebug() << obs;
        }

        if (type == (typeid (Obstacles)) || (type == typeid(WaterGirl))|| type == typeid(FireBoy)) {  //note this is all obstacles (can't pass through them)
            Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);
            qDebug() << "Colliding item : " << ptr->getType();

            if (ptr -> getType() == "Side")
            {   if (direction ==1)
                {
                    right = false;
                }
                else if(direction == 2)
                {
                    left = false;
                }
                qDebug()<<"Player is touching SIDE";
            }

            if (ptr -> getType() == "Pav")
            {   setPos(x(), y());
                qDebug()<<"Player is touching pavement";
            }
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


