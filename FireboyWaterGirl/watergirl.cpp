#include "watergirl.h"
#include <QGraphicsScene>
#include<QGraphicsRectItem>
#include <QBrush>
#include <QTimer>

WaterGirl::WaterGirl(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/WaterGirl.png").scaled(45,65, Qt::KeepAspectRatio)); // fix scaling
}

void WaterGirl::keyPressEvent(QKeyEvent* event) {
    right= true;
    left = true;
    gravity();
    boundries();
    if (event->key() == Qt::Key_Q) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            direction = 2;
            jump(0);
        }
    } else if (event->key() == Qt::Key_E) {
            if (!isJumping) {
                isJumping = true;
                originalY = y();
                direction = 1;
                jump(0);
            }
    }else if (event->key() == Qt::Key_W) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            direction = 0;
            jump(0);
        }
    } else if ((event->key() == Qt::Key_A)&& left) {
        moveBy(-10, 0);
        direction = 2;
    } else if ((event->key() == Qt::Key_D)&& right) {
        moveBy(10, 0);
        direction = 1;
    }
}

void WaterGirl::jump(int jumpStep) {
    if (jumpStep < 5) {
        switch (direction){
        case 0:
            moveBy(0, -10);
            break;
        case 1:
            moveBy(15, -10);
            break;
        case 2:
            moveBy(-15, -10);
            break ;
        }
        ++jumpStep;
        if (hitPavement())                                                                          //if hit pavement at the top, start falling, skip to secind else if
        {
            direction = 0;
            jumpStep = 5;
        }
        if (hitSide())                                                                              //if hit side go back down and skip to last else if
        {
            boundries();
            direction = 0;
        }
        QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });
    }
    else if (y() != originalY)
    {
        switch (direction){
        case 0:
            moveBy(0, 10);
            break;
        case 1:
            moveBy(15, 10);
            break;
        case 2:
            moveBy(-15, 10);
            break ;
        }
        QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });
    }
    else if (y() == originalY)
    {
        isJumping = false; // Reset isJumping flag
        return;
    }
}

void ::WaterGirl::boundries()
{
    if (hitSide())
    {
        if (direction ==1)
        {
            right = false;
        }
        else if(direction == 2)
        {
            left = false;
        }
        QTimer::singleShot(20, this, [this]() { boundries(); });
    }
    else
    {
        right = true;
        left = false;
        return;
    }
}


