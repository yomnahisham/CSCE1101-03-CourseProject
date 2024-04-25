#include "watergirl.h"
#include "windowmanager.h"
#include "layout.h"
#include <QGraphicsScene>
#include <QTimer>

WaterGirl::WaterGirl(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/WaterGirl.png").scaled(45,65, Qt::KeepAspectRatio)); // fix scaling
}

void WaterGirl::keyPressEvent(QKeyEvent* event) {
    right= true;
    left = true;
    gravity();
    boundries();

    if (event->key() == Qt::Key_E && right) {
        if (!isJumping) {
            isJumping = true;
            direction = 1;
            Leap(0,10);
        }
    } else if (event->key() == Qt::Key_Q && left) {
        if (!isJumping) {
            isJumping = true;
            direction = 2;
            Leap(0,10);
        }
    }else if (event->key() == Qt::Key_W)  {
        if (!isJumping) {
            isJumping = true;
            direction = 0;
            jump(0,10);
        }
    } else if ((event->key() == Qt::Key_A)&& left) {
        direction = 2;
        if (isJumping){
            isJumping = false;
            jump (0, 20);
        }
        else
            moveBy(-10, 0);
    } else if ((event->key() == Qt::Key_D)&& right) {
        direction = 1;
        if (isJumping){
            isJumping = false;
            jump (0, 20);
        }
        else
            moveBy(10, 0);
    }
    checkCollisions();
}

void WaterGirl::Leap(int Step, int height) {
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



void WaterGirl::jump(int jumpStep, int height) {
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
            moveBy(5, -height);
            break;
        case 2:
            moveBy(-5, -height);
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


void WaterGirl::boundries()
{
    right = true;
    left = true;

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
        qDebug()<< "going down slope";
        right = true;
        left = true;
    }


}

void WaterGirl::kill(){

    WindowManager Manager;
    Manager.endWindow(WindowManager::lev);
    Manager.showWindow(WindowManager::over);

}
