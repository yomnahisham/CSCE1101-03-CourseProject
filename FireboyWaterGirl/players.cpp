#include "players.h"
#include "obstacles.h"
#include "layout.h"
#include <QTimer>


Players::Players(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    QTimer * timer = new QTimer(this);
    // connect function to check for collisions every here and there
    connect(timer, &QTimer::timeout, [=]() {
        checkCollisions();
    });    timer->start(500);
}

bool Players::hitPavement()
{
    // checks for collision with pavement
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
    // checks for collision with pavement or ceiling
    if (!hitPavement()||hitCeiling())
    {
        moveBy (0,2); // moves accordingly
        QTimer::singleShot(10, this, [this]() { gravity(); }); //keeps a single shot timere to move again

    }
    else
    {
        setPos(x(), y());
        return;
    }

}

bool Players:: hitSide ()
{
    // checks for collision with side
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
    // checks for collision with ceiling
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
    // checks for collision with any item and handles it using handlecollision in layout
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
