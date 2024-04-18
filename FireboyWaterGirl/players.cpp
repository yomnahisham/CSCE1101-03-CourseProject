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
        QGraphicsItem* obs = (colliding_items[i]);

        qDebug() << "Colliding item type: " << type.name();

        if (type == (typeid (Obstacles)) || (type == typeid(WaterGirl))|| type == typeid(FireBoy)) {  //note this is all obstacles (can't pass through them)
            qDebug()<<"Player is touching obstacle";
            Obstacles* ptr = dynamic_cast<Obstacles*>(obs);

            if (ptr &&ptr -> getType() == Obstacles::Pavement)
            {   setPos(x(), y());
                qDebug()<<"Player is touching pavement";
            }
            if (*type.name() == Obstacles::Side)
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


