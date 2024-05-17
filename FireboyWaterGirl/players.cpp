#include "players.h"
#include "obstacles.h"
#include "layout.h"
#include <QTimer>


Players::Players(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        checkCollisions();
    });    timer->start(500);
}

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

void Players::gravity ()
{

    if (!hitPavement()||hitCeiling())
    {
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
