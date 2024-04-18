#include "watergirl.h"
#include "layout.h"
#include "obstacles.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QTimer>

WaterGirl::WaterGirl(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/WaterGirl.png").scaled(45,65, Qt::KeepAspectRatio)); // fix scaling
}

void WaterGirl::keyPressEvent(QKeyEvent* event) {
    gravity();
    if (event->key() == Qt::Key_W) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            jump(15);
        }
    } else if (event->key() == Qt::Key_A) {
        moveBy(-10, 0);
    } else if (event->key() == Qt::Key_D) {
        moveBy(10, 0);
    }
}

void WaterGirl::jump(int jumpStep) {
    if (jumpStep < 20) {
        moveBy(0, -5);
        ++jumpStep;
        QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });
    } else {
        isJumping = false;
        setPos(x(), originalY);
    }
}

void WaterGirl::gravity ()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Obstacles))
        {
            setPos(x(), y());
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
