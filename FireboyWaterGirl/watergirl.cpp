#include "watergirl.h"
#include "windowmanager.h"
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
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_E || event->key() == Qt::Key_W) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            if (event->key() == Qt::Key_Q)
                direction = 2;
            else if (event->key() == Qt::Key_E)
                direction = 1;
            else if (event->key() == Qt::Key_W)
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
        int dy = -10;
        if (direction == 1)
            moveBy(15, dy);
        else if (direction == 2)
            moveBy(-15, dy);
        ++jumpStep;
        if (hitPavement()) {
            direction = 0;
            jumpStep = 5;
        }
        if (hitSide()) {
            boundries();
            direction = 0;
        }
        QTimer::singleShot(40, this, [this, jumpStep]() { jump(jumpStep); });
    } else if (y() != originalY) {
        int dy = 10;
        if (direction == 1)
            moveBy(15, dy);
        else if (direction == 2)
            moveBy(-15, dy);
        QTimer::singleShot(40, this, [this, jumpStep]() { jump(jumpStep); });
    } else {
        isJumping = false;
    }
}

void WaterGirl::boundries()
{
    if(hitSide())
    {
        if(direction == 1)
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
        left = true;
    }
}

void WaterGirl::kill(){
    delete this;
    WindowManager Manager;
    Manager.showWindow(WindowManager::over);
    hide();
}
