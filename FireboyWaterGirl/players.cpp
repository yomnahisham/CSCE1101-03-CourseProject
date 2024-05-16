#include "players.h"
#include "obstacles.h"
#include "layout.h"
#include <QTimer>


Players::Players(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {}
bool Players::hitPavement()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);
        if (ptr && ((ptr->objectName() == "Pavement")||(ptr->objectName() == "Block"))) {
            return true;}
    }
    return false;
}

bool Players::hitFloor()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);
        if (ptr && ((ptr->objectName() == "SlidingFloor1")||(ptr->objectName() == "SlidingFloor2"))) {
            return true;}
    }
    return false;
}

void Players::gravity ()
{

    if (!hitPavement()||hitCeiling())
    {
        qDebug()<< "in the air";
        moveBy (0,2);
        QTimer::singleShot(10, this, [this]() { gravity(); });

    }
    else
    {
        setPos(x(), y());
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

bool Players:: hitSlope ()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);
        if ((ptr) && (ptr -> objectName() == "Slope")) {
            return true;
        }
    }
    return false;
}

bool Players:: hitCeiling ()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);
        if ((ptr) && (ptr -> objectName() == "Ceiling")) {
            return true;
        }
    }
    return false;
}

void Players::checkCollisions ()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);
        Layout* lay = dynamic_cast<Layout*>(this->scene());
        if (ptr)
        {
            lay -> handleCollisions(this, ptr);
        }

    }
}



//Players::~Players() {}

