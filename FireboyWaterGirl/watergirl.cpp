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
        direction = 2;
        if (isJumping){
            isJumping = false;
            moveBy (-20,0);
            jump (5, 5);
        }
        else
            moveBy(-10, 0);
    } else if ((event->key() == Qt::Key_D)&& right) {
        direction = 1;
        if (isJumping){
            isJumping = false;
            moveBy (20,0);
            jump (5, 5);
        }
        else
            moveBy(10, 0);
    }
    checkCollisions();
}

void WaterGirl::jump(int jumpStep, int height) {
    if (jumpStep < 5) {
        switch (direction){
        case 0:
            moveBy(0, -height);
            break;
        case 1:
            moveBy(15, -height);
            break;
        case 2:
            moveBy(-15, -height);
            break ;
        }
        ++jumpStep;

        if (hitCeiling())                                                                          //if hit pavement at the top, start falling, skip to second else if
        {
            qDebug()<< "hit ceiling";
            direction = 0;
            jumpStep = 5;
            /*while(hitPavement())
            {moveBy(0, height);}
            qDebug()<< "boy moved";*/
        }

        if (hitSide())                                                                              //if hit side go back down and skip to second else if
        {
            qDebug()<< "hit side";
            boundries();
            direction = 0;
            jumpStep = 5;

        }

        if (hitSlope())
        {

        }

        QTimer::singleShot(40, this, [this, jumpStep]() { jump(jumpStep); });
    }
    else if (!hitPavement()||hitCeiling())
    {
        qDebug()<< "going down";

        switch (direction){
        case 0:
            moveBy(0, height);
            break;
        case 1:
            moveBy(15, height);
            break;
        case 2:
            moveBy(-15, height);
            break ;
        }
        QTimer::singleShot(40, this, [this, jumpStep]() { jump(jumpStep); });
    }
    else if (hitPavement()&& !hitCeiling()&&!hitSide())
    {
        qDebug()<< "jump done";
        setPos(x(), y());
        isJumping = false; // Reset isJumping flag
        return;
    }

}

void WaterGirl::boundries()
{
    if ((hitSlope()&&!isJumping) || (hitSlope() && y() > originalY))
    {
        if (y() > originalY)
        {
            if (direction == 1 &&!isJumping)
                right = false;
            else if (direction == 2 &&!isJumping)
                left = false;


        }
        else if (direction == 2)
        {
            left = false;
        }
        QTimer::singleShot(20, this, [this]() { boundries(); });

    }else if(hitSide())
    {
        if (direction == 1)
        {
            right = false;
            moveBy(-10,0);
        }
        else if (direction == 2)
        {
            left = false;
            moveBy(10,0);
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
