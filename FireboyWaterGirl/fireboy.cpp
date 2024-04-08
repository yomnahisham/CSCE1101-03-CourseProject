#include "FireBoy.h"
#include <QBrush>

FireBoy::FireBoy(QGraphicsItem* parent) : Players(parent) {
    setRect(0, 0, 50, 50); //edit later
    setBrush(Qt::red);
}

void FireBoy::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Up) {
        moveBy(0, -10);
    } else if (event->key() == Qt::Key_Down) {
        moveBy(0, 10);
    } else if (event->key() == Qt::Key_Left) {
        moveBy(-10, 0);
    } else if (event->key() == Qt::Key_Right) {
        moveBy(10, 0);
    }
}
