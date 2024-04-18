#include "watergirl.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QTimer>

WaterGirl::WaterGirl(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/WaterGirl.png").scaled(45,65, Qt::KeepAspectRatio)); // fix scaling
}

void WaterGirl::keyPressEvent(QKeyEvent* event) {
    Players::right= true;
    Players::left = true;
    Players::gravity();
    if (event->key() == Qt::Key_W) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            jump(15);
        }
        Players::direction = 0;
    } else if ((event->key() == Qt::Key_A)&& Players::left) {
        moveBy(-10, 0);
        Players::direction = 2;
    } else if ((event->key() == Qt::Key_D)&& Players::right) {
        moveBy(10, 0);
        Players::direction = 1;
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


