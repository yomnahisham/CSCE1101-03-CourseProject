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

    if (event->key() == Qt::Key_Shift)  {           //shift key jumps right
        if (!isJumping) {
            direction = 1;
            isJumping = true;
            upLevel = false;
            jump(0);
            qDebug()<< "jumped right";
        }
    }else if (event->key() == Qt::Key_Slash)  {     //"/" key jumps right
        if (!isJumping) {
            direction = 2;
            isJumping = true;
            upLevel = false;
            jump(0);
            qDebug()<< "jumped left";
        }
    }else if (event->key() == Qt::Key_Up)  {
        if (!isJumping) {
            direction = 0;
            isJumping = true;
            upLevel = false;
            jump(0);
            qDebug()<< "jumped up";
        }
    } else if ((event->key() == Qt::Key_Left)) {
        direction = 2;
        moveBy(-10, 0);
        //qDebug()<< "moved left";
    } else if ((event->key() == Qt::Key_Right)) {
        direction = 1;
        moveBy(10, 0);
        //qDebug()<< "moved right";
    }

    checkCollisions();
}

void FireBoy::jump(int jumpStep) {
    if (jumpStep < 14) {                 //part 1: upwards arc of jump
        qDebug() << "part 1";

        switch (direction){
        case 0:
            moveBy(0, -7.5);
            break;
        case 1:
            moveBy(13.5, -7.5);
            break;
        case 2:
            moveBy(-13.5, -7.5);
            break ;
        }
        ++jumpStep;

        if (jumpStep == 14) // when jumpStep reaches 5 without the help of hitCeiling or hitSide then there is no ceiling there
        {
            upLevel = true;
            qDebug()<<"activating uplevel";
        }

        if (hitCeiling())
        {
            moveBy(0, 7.5);                  //move down 1 jumpStep
            jumpStep = 14;                   //fast track to part 2
            qDebug() << "Hit ceiling";
        }

        if (hitPavement())
        {
            jumpStep = 14;                   //fast track to last else if statement
        }

        if (hitSide())
        {   qDebug() << "Hit side";
            if (direction == 1)
                moveBy(-13.5, 0);         //move back 1 jumpStep
            else if (direction ==2)
                moveBy(13.5, 0);           //move back 1 jumpStep

            direction = 0;              //change direction so fall of jump can be straight dowwards
            jumpStep =14;                //fast track to part 2
        }

        QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });   //repeatedly call Jump with new jumpstep
    }
    else if (!hitPavement())            //part 2: downwards arc of jump
    {
        qDebug() << "part 2";

        if (!upLevel)
        {
            qDebug() << " not up level";

            switch (direction){
            case 0:
                moveBy(0, 7.5);
                break;
            case 1:
                moveBy(13.5, 7.5);
                break;
                qDebug() << "moved down";
            case 2:
                moveBy(-13.5, 7.5);
                break ;
            }
        }else if (upLevel)
        {
            qDebug() << " up level";

            switch (direction){
            case 0:
                moveBy(0, 7.5);
                break;
            case 1:
                moveBy(5, 7.5);
                break;
                qDebug() << "moved down";
            case 2:
                moveBy(-5, 7.5);
                break ;
            }
        }

        if (hitSide())
        {   qDebug() << "Hit side";
            if (direction == 1)
                moveBy(-13.5, 0);         //move back 1 jumpStep
            else if (direction ==2)
                moveBy(13.5, 0);           //move back 1 jumpStep

            direction = 0;              //change direction so fall of jump can be straight dowwards
        }

        if (hitPavement())              //if hit pavement: end jump and return
        {
            qDebug() << "end jump";
            isJumping = false;
            gravity();
            return;
        } else                          //else if still in the air call Jump again (jumpstep is already 5 so it will keep calling part 2 untill it reaches condition and returns
            QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });
    }else if (hitPavement())              //if hit pavement: end jump and return
    {
        qDebug() << "end jump";
        gravity();
        isJumping = false;
        return;
    }
}


void FireBoy::boundries()
{

    if (hitSide())
    {
        if (direction == 1)
        {
            moveBy(-10,0);
        }
        else if (direction == 2)
        {
            moveBy(10,0);
        }
    }

    //qDebug()<< y();

    //level 1 specific trouble spots
    if (x() > 920 && y() > 632 && y() < 695)
    {
        setPos(845, 650);
        gravity();
    }

    if (x() < 131 && y() > 480 && y() < 525 )
    {
        setPos(160, 500);
        gravity();
    }

    if (x() > 887 && y() > 330 && y() < 380)
    {
        setPos(830, 360);
        gravity();
    }

    return;
}

void FireBoy::kill(){
    hide();
    WindowManager Manager;
    Manager.showWindow(WindowManager::over);
}

bool FireBoy::atDoor()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        Obstacles* ptr = dynamic_cast<Obstacles*>(colliding_items[i]);
        if (ptr && ((ptr->objectName() == "FD")) ){
            return true;}
    }
    return false;
}


/*
 * //key press event code
 *    }else if (event->key() == Qt::Key_Up)  {
        direction = 0;
        if (!isJumping) {
            isJumping = true;
            jump(0);
            qDebug()<< "jumped up";
        }
    } else if ((event->key() == Qt::Key_Left)) {
        direction = 2;
        if (isJumping){
            isJumping = false;
            isJumping = true;
            jump (0);
            qDebug()<< "jumped left";

        }
        else
        {    moveBy(-10, 0);
        qDebug()<< "moved left";


    } else if ((event->key() == Qt::Key_Right)) {
        direction = 1;
        if (isJumping){
            isJumping = false;
            isJumping = true;
            jump (0);
            qDebug()<< "jumped right";
        }
        else
        {    moveBy(10, 0);
            qDebug()<< "moved right"; }

    }

//boundries slope code

    if ((hitSlope()&&!isJumping) || (hitSlope() &&!isJumping && y() > originalY))
    {

        if (direction == 1)
        {
            moveBy(-10, 0);
            qDebug()<< "going up a slope, cant go RIGHT";
        }
        else if (direction == 2)
        {
            moveBy(10, 0);
            qDebug()<< "going up a slope, cant go LEFT";
        }
    }

    if (hitSlope() && y() < originalY) // check if it enters if
    {
        setPos(x(), y());
        qDebug()<< "going down slope";
    }
*/
