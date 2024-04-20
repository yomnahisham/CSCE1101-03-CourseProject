#include "players.h"
#include "obstacles.h"
#include "watergirl.h"
#include "fireboy.h"
#include <QTimer>


Players::Players(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {}
bool Players::hitPavement()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);

        if (ptr) {
            if (ptr->objectName() == "Pavement") {
                return true;
            } else if (ptr->objectName() == "Fire") {
                ptr->handleCollisions(this); // call handlecollision in obstacles
            }
        }
    }
    return false;
}

void Players::gravity ()
{
    if (!hitPavement())
    {
        moveBy (0,2);
        QTimer::singleShot(10, this, [this]() { gravity(); });
    }
    else
    {
        return;
    }
}

bool Players:: hitSide ()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);
        if ((ptr) && (ptr -> objectName() == "Side")) {
            return true;
        }
    }
    return false;
}

//Players::~Players() {}


/*
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
 */

/*    QList<QGraphicsItem *> colliding_items = collidingItems();                      //create a list of colliding items

    for (int i = 0, n = colliding_items.size(); i < n; ++i){                        //go through each  item
        const std::type_info& type = typeid(*(colliding_items[i]));                 //type will cary the type id of the colliding items

        if (type == (typeid (Obstacles)) || (type == typeid(WaterGirl))|| type == typeid(FireBoy)) {  //note this is all obstacles (can't pass through them)
            Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);          //dynamically casting the colliding items to a ptr of type obstacles

            if (ptr -> getType() == "Pav")                                          //if the colliding item (ptr) type is "Pav"
            {   setPos(x(), y());                                                   //stay at the same y
                qDebug()<<"Player is touching PAV";
            }

            if (ptr -> getType() == "Side")                                         //if the colliding item (ptr) type is "Side"
            {   if (direction ==1)                                                  //if player was moving right
                {
                    qDebug()<<"Player can't move right";
                    right = false;                                                  //disable ability to go right
                }
                else if(direction == 2)                                             //if player was moving left
                {
                    qDebug()<<"Player cna't move left";
                    left = false;                                                   //disable ability to go left
                }
                qDebug()<<"Player is touching SIDE";
            }


            return;                                                                 //go out of gravity() and return to implement key press events
        }
        else                                                                        //if no obstacle is touching players
        {
            qDebug()<<"Player is in the air";
            moveBy (0,2);
            QTimer::singleShot(20, this, [this]() { gravity(); });                  //go downwards and recursively call the function untill it collides into pavement
        }
    }*/
