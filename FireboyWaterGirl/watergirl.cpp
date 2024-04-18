#include "watergirl.h"
#include <QBrush>
#include <QTimer>

WaterGirl::WaterGirl(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/watergirl.png")); // fix scaling
    if (QPixmap(":/image/img/fireboy.png").isNull()) {
        qDebug() << "Failed to load WaterGirl";
    } else {
        qDebug() << "WaterGirl loaded successfully!";}
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
