#include "WaterGirl.h"
#include <QBrush>

WaterGirl::WaterGirl(QGraphicsItem* parent) : Players(parent) {
    setRect(0, 0, 50, 50); //edit later
    setBrush(Qt::blue);
}

void WaterGirl::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_W) {
        moveBy(0, -10);
    } else if (event->key() == Qt::Key_S) {
        moveBy(0, 10);
    } else if (event->key() == Qt::Key_A) {
        moveBy(-10, 0);
    } else if (event->key() == Qt::Key_D) {
        moveBy(10, 0);
    }
}
