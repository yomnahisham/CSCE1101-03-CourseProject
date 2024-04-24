#include "fireboy.h"
#include "windowmanager.h"
#include <QBrush>
#include <QTimer>


FireBoy::FireBoy(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/FireBoy.png").scaled(50,70, Qt::KeepAspectRatio)); // fix scaling
}

void FireBoy::keyPressEvent(QKeyEvent* event) {
    originalY = y();
    right= true;
    left = true;
    gravity();
    boundries();

    if (event->key() == Qt::Key_Shift&& right) {
        if (!isJumping) {
            isJumping = true;
            direction = 1;
            jump(0);
        }
    } else if (event->key() == Qt::Key_Slash && left) {
        if (!isJumping) {
            isJumping = true;
            direction = 2;
            jump(0);
        }
    } else if (event->key() == Qt::Key_Up)  {
        if (!isJumping) {
            isJumping = true;
            direction = 0;
            jump(0);
        }
    } else if ((event->key() == Qt::Key_Left)&&left) {
        direction = 2;
        if (isJumping){
            isJumping = false;
            jump (0, 11);
        }
        else
            moveBy(-10, 0);

    } else if ((event->key() == Qt::Key_Right)&&right) {
        direction = 1;
        if (isJumping){
            isJumping = false;
            jump (0, 11);
        }
        else
            moveBy(10, 0);

    }
    checkCollisions();
}

void FireBoy::jump(int jumpStep, int height) {
    if (jumpStep < 5) {
        switch (direction){
        case 0:   
            moveBy(0, -height);
            break;
        case 1:
            if (height > 10)
                moveBy(5, -height);
            else
                moveBy(16, -height);
            break;
        case 2:
            if (height > 10)
                moveBy(-5, -height);
            else
                moveBy(-16, -height);
            break ;
        }
        ++jumpStep;

        if (hitCeiling())                                                                          //if hit pavement at the top, start falling, skip to secind else if
        {
            //qDebug()<< "hit ceiling";
            direction = 0;
            jumpStep = 5;
        }

        if (hitSide())                                                                              //if hit side go back down and skip to last else if
        {
            //qDebug()<< "hit side";
            boundries();
            direction = 0;
        }

        if (hitSlope())
        {
            //qDebug()<< "hit slope";
            boundries();
            setPos(x(), y());
            isJumping = false; // Reset isJumping flag
            return;
        }

        QTimer::singleShot(40, this, [this, jumpStep]() { jump(jumpStep); });
    }
    else if (!hitPavement()||hitCeiling())
    {
        //qDebug()<< "going down";

        switch (direction){
        case 0:
            moveBy(0, height);
            break;
        case 1:
            if (height > 10)
                moveBy(5, height);
            else
                moveBy(16, height);
            break;
        case 2:
            if (height > 10)
                moveBy(-5, height);
            else
                moveBy(-16, height);
            break ;
        }
        QTimer::singleShot(40, this, [this, jumpStep]() { jump(jumpStep); });
    }
    else if (hitPavement()&&hitSlope()&& !hitCeiling()&&!hitSide())
    {
        //qDebug()<< "jump done";
        setPos(x(), y());
        isJumping = false; // Reset isJumping flag
        return;
    }
}

void FireBoy::boundries()
{
    right = true;
    left = true;

    if ((hitSlope()&&!isJumping) || (hitSlope() && y() >= originalY))
    {
        if (direction == 1)
        {
            right = false;
        }
        else if (direction == 2)
        {
            left = false;
        }
        QTimer::singleShot(20, this, [this]() { boundries(); });

    }
    if(hitSide())
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
}

void FireBoy::kill(){
    hide();
    WindowManager Manager;
    Manager.showWindow(WindowManager::over);
}
