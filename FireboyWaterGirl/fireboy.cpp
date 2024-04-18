#include "fireboy.h"
#include <QBrush>
#include <QTimer>


FireBoy::FireBoy(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/FireBoy.png").scaled(100,100, Qt::KeepAspectRatio)); // fix scaling
}

void FireBoy::keyPressEvent(QKeyEvent* event) {

    if (event->key()  == Qt::Key_Up)
    {
        upKey = true;
    }
    if (event->key() == Qt::Key_Right)
    {
        rightKey = true;
    }
    if (event->key() == Qt::Key_Left)
    {
        leftKey = true;
    }

    if ((upKey) && (rightKey)) {
        qDebug() << "up and right key is pressed";
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            jump(0, 1);
        }
        QTimer::singleShot(200, this, [this]() {
            upKey = false;
            rightKey = false; });
    }else if ((upKey) && (leftKey)) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            jump(0,2);
        }
        QTimer::singleShot(200, this, [this]() {
            upKey = false;
            leftKey = false; });
    }else if (event->key() == Qt::Key_Up) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            jump(0, 0);
        }
        qDebug() << "up key is from event";

    } else if (event->key() == Qt::Key_Left) {
        moveBy(-10, 0);
    } else if (event->key() == Qt::Key_Right) {
        moveBy(10, 0);
    }
}

void FireBoy::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Up) {
        upKey = false;
        qDebug() << "up key is false";
    }
    if (event->key() == Qt::Key_Right) {
        rightKey = false;
    }
    if (event->key() == Qt::Key_Left) {
        leftKey = false;
    }

    if (!upKey && !rightKey) {
        isJumping = false; // Reset isJumping flag if no jump key is pressed
    }
}

void FireBoy::jump(int jumpStep, int direction) {
    if (direction == 1){
        if (jumpStep < 5) {    //if jumping right
            moveBy(5, -10);
            ++jumpStep;
            QTimer::singleShot(20, this, [this, jumpStep, direction]() { jump(jumpStep, direction); });
        }
        else if (y() != originalY)
        {
            moveBy(5, 10);
            QTimer::singleShot(20, this, [this, jumpStep, direction]() { jump(jumpStep, direction); });
        }
        else if (y() == originalY)
        {
            isJumping = false; // Reset isJumping flag
            return;
        }
    }else if (direction == 2){
        if (jumpStep < 5) {    //if jumping left
            moveBy(-5, -10);
            ++jumpStep;
            QTimer::singleShot(20, this, [this, jumpStep, direction]() { jump(jumpStep, direction); });
        }
        else if (y() != originalY)
        {
            moveBy(-5, 10);
            QTimer::singleShot(20, this, [this, jumpStep, direction]() { jump(jumpStep, direction); });
        }
        else if (y() == originalY)
        {
            isJumping = false; // Reset isJumping flag
            return;
        }
    } else if (direction == 0){
        if (jumpStep < 5) {    //if jumping only
            moveBy(0, -10);
            ++jumpStep;
            QTimer::singleShot(20, this, [this, jumpStep, direction]() { jump(jumpStep, direction); });
        }
        else if (y() != originalY)
        {
            moveBy(0, 10);
            QTimer::singleShot(20, this, [this, jumpStep, direction]() { jump(jumpStep, direction); });
        }
        else if (y() == originalY)
        {
            isJumping = false; // Reset isJumping flag
            return;
        }
    }    return;
}
