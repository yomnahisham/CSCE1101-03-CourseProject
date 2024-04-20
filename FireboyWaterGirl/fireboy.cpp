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
        qDebug() << "up and right key is pressed";
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
            moveBy (-20,0);
            jump (5, 5);
        }
        else
            moveBy(-10, 0);

    } else if ((event->key() == Qt::Key_Right)&&right) {
        direction = 1;
        if (isJumping){
            isJumping = false;
            moveBy (20,0);
            jump (5, 5);
        }
        else
            moveBy(10, 0);

    }
}

void FireBoy::jump(int jumpStep, int height) {
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

        if (hitCeiling())                                                                          //if hit pavement at the top, start falling, skip to secind else if
        {
            qDebug()<< "hit ceiling";
            direction = 0;
            jumpStep = 5;
            /*while(hitPavement())
            {moveBy(0, height);}
            qDebug()<< "boy moved";*/
        }

        if (hitSide())                                                                              //if hit side go back down and skip to last else if
        {
            qDebug()<< "hit side";
            boundries();
            direction = 0;
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

void FireBoy::boundries()
{
    if ((hitSlope()&&!isJumping) || (hitSlope() && y() > originalY))
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

void FireBoy::kill(){
    delete this;
    WindowManager Manager;
    Manager.showWindow(WindowManager::over);
}
