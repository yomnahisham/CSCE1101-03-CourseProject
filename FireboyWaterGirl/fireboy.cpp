#include "FireBoy.h"
#include <QBrush>
#include <QTimer>

FireBoy::FireBoy(QGraphicsItem* parent) : Players(parent) {
    setRect(0, 0, 50, 50); //edit later
    setBrush(Qt::red);
}

void FireBoy::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Up) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            jump(15);
        }
    } else if (event->key() == Qt::Key_Left) {
        moveBy(-10, 0);
    } else if (event->key() == Qt::Key_Right) {
        moveBy(10, 0);
    }
}

void FireBoy::jump(int jumpStep) {
    if (jumpStep < 20) {
        moveBy(0, -5);
        ++jumpStep;
        QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });
    } else {
        isJumping = false;
        setPos(x(), originalY);
    }
}
