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
            originalPos = pos();
            jump(15); // Initial jump step
        }
    } else if (event->key() == Qt::Key_Left) {
        moveBy(-10, 0);
    } else if (event->key() == Qt::Key_Right) {
        moveBy(10, 0);
    }
}

void FireBoy::jump(int jumpStep) {
    if (jumpStep < 20) { // Limit jump height
        moveBy(0, -5); // Move up
        ++jumpStep;
        QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });
    } else {
        isJumping = false;
        setPos(originalPos); // Return to original position
    }
}
