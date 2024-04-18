#include "watergirl.h"
#include "layout.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QTimer>

WaterGirl::WaterGirl(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/WaterGirl.png").scaled(65,80, Qt::KeepAspectRatio)); // fix scaling
    qDebug()<<"water girl successfully constructed";
}

void WaterGirl::setScene(Layout*s)
{
    scene = new Layout(s);

}

void WaterGirl::keyPressEvent(QKeyEvent* event) {
    //gravity();
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
    if (!(this -> collidesWithItem(scene-> pav)) && ! isJumping)
    {
        moveBy (0,10);
        QTimer::singleShot(20, this, [this]() { gravity(); });
    }
}
