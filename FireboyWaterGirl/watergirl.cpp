#include "WaterGirl.h"
#include <QBrush>
#include <QTimer>

WaterGirl::WaterGirl(QGraphicsItem* parent) : Players(parent) {
    setRect(0, 0, 50, 50); //edit later
    setBrush(Qt::blue);
}

void WaterGirl::keyPressEvent(QKeyEvent* event) {
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
