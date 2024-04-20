#include "fireboy.h"
#include "windowmanager.h"
#include <QBrush>
#include <QTimer>


FireBoy::FireBoy(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/FireBoy.png").scaled(65,80, Qt::KeepAspectRatio)); // fix scaling
}

void FireBoy::keyPressEvent(QKeyEvent* event) {
    right= true;
    left = true;
    gravity();
    boundries();

    if (event->key() == Qt::Key_Shift&& right) {
        qDebug() << "up and right key is pressed";
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            direction = 1;
            jump(0);
        }
    } else if (event->key() == Qt::Key_Slash && left) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            direction = 2;
            jump(0);
        }
    } else if (event->key() == Qt::Key_Up)  {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            direction = 0;
            jump(0);
        }
    } else if ((event->key() == Qt::Key_Left)&&left) {
        direction = 1;
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
        QTimer::singleShot(40, this, [this, jumpStep]() { jump(jumpStep); });
    }
    else if (!hitPavement())
    {
        qDebug()<< "jump turn not hit pav";

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
    else if (hitPavement())
    {
        qDebug()<< "jump turn  HIT";

        isJumping = false; // Reset isJumping flag
        return;
    }
}

void FireBoy::boundries()
{
    if (hitSide())
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
