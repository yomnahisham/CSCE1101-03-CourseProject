#include "fireboy.h"
#include "layout.h"
#include "windowmanager.h"
#include <QTimer>


FireBoy::FireBoy(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/FireBoy.png").scaled(50,70, Qt::KeepAspectRatio)); // fix scaling
}

void FireBoy::keyPressEvent(QKeyEvent* event) {
    gravity();
    boundries();

    if (event->key() == Qt::Key_Shift && right) {
        if (!isJumping) {
            isJumping = true;
            direction = 1;
            Leap(0,9);
        }
    } else if (event->key() == Qt::Key_Slash && left) {
        if (!isJumping) {
            isJumping = true;
            direction = 2;
            Leap(0,9);
        }
    }else if (event->key() == Qt::Key_Up)  {
        if (!isJumping) {
            isJumping = true;
            direction = 0;
            jump(0,20);
        }
    } else if ((event->key() == Qt::Key_Left)&&left) {
        direction = 2;
        if (isJumping){
            isJumping = false;
            isJumping = true;
            jump (0, 20);
        }
        else
            moveBy(-10, 0);

    } else if ((event->key() == Qt::Key_Right)&&right) {
        direction = 1;
        if (isJumping){
            isJumping = false;
            isJumping = true;
            jump (0, 20);
        }
        else
            moveBy(10, 0);

    }
    checkCollisions();

}

void FireBoy::Leap(int Step, int height) {
    QGraphicsScene* sce = this -> scene();
    if (Step < 7 && isJumping) {
        switch (direction){
        case 1:
            moveBy(25, -height);
            break;
        case 2:
            moveBy(-25, -height);
            break ;
        }
        ++Step;
        QTimer::singleShot(40, this, [this, Step, height]() { Leap(Step, height); });

        if (hitCeiling())
        {
            gravity();         //make him fall
            isJumping = false;  //end jump
            right = true;
            left = true;
            qDebug()<< "return from jump";
            return;
        }
        if (hitSide())
        {
            gravity();
            boundries() ;           //make him fall
            if (hitSide())
            {
                Layout::closeGame(sce);
                kill ();
            }
            else{
                isJumping = false;  //end jump
                right = true;
                left = true;
                qDebug()<< "return from jump";
                return;}
        }
    }else if (hitPavement()||hitSlope())
    {
        //qDebug()<< "jump done";
        setPos(x(), y());
        isJumping = false; // Reset isJumping flag
        right = true;
        left = true;
        return;
    }

}



void FireBoy::jump(int jumpStep, int height) {
    QGraphicsScene* sce = this -> scene();
    if (direction != 0)
    {
        right = false;
        left = false;
    }
    if (jumpStep < 7 && isJumping) {
        switch (direction){
        case 0:
            moveBy(0, -height);
            break;
        case 1:
            moveBy(7, -height);
            break;
        case 2:
            moveBy(-7, -height);
            break ;

        }
        ++jumpStep;
        QTimer::singleShot(40, this, [this, jumpStep, height]() { jump(jumpStep, height); });

        if (hitCeiling())
        {
            gravity ();         //make him fall
            isJumping = false;  //end jump
            right = true;
            left = true;
            qDebug()<< "return from jump";
            return;
        }
        if (hitSide())
        {
            gravity ();
            boundries() ;           //make him fall
            if (hitSide())
            {
                Layout::closeGame(sce);
                kill ();
            }
            else{
            isJumping = false;  //end jump
            right = true;
            left = true;
            qDebug()<< "return from jump";
            return;}
        }

    }else if (hitPavement()||hitSlope())
    {
        //qDebug()<< "jump done";
        setPos(x(), y());
        isJumping = false; // Reset isJumping flag
        right = true;
        left = true;
        return;
    }

}

void FireBoy::boundries()
{
    right = true;
    left = true;

    if(hitSide())
    {
        if (direction == 1)
        {
            right = false;
            moveBy(-20,0);
        }
        else if (direction == 2)
        {
            left = false;
            moveBy(20,0);
        }
    }

    if ((hitSlope()&&!isJumping) || (hitSlope() &&!isJumping && y() > originalY))
    { 

        if (direction == 1)
        {
            right = false;
            qDebug()<< "going up a slope, cant go RIGHT";
        }
        else if (direction == 2)
        {
            left = false;
            qDebug()<< "going up a slope, cant go LEFT";
        }
    }

    if (hitSlope() && y() < originalY) // check if it enters if
    {
        setPos(x(), y());
        qDebug()<< "going down slope";
        right = true;
        left = true;
    }

    return;
}

void FireBoy::kill(){
    hide();
    WindowManager Manager;
    Manager.showWindow(WindowManager::over);
}

/*
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
    isJumping = false; // Reset isJumping flag
    return;
    }*/
