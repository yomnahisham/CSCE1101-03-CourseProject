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
        }
    }else if (event->key() == Qt::Key_Slash)  {     //"/" key jumps left
        if (!isJumping) {
            direction = 2;
            isJumping = true;
            upLevel = false;
            jump(0);
        }
    }else if (event->key() == Qt::Key_Up)  {    //move up (jump)
        if (!isJumping) {
            direction = 0;
            isJumping = true;
            upLevel = false;
            jump(0);
        }
    } else if ((event->key() == Qt::Key_Left)) {    //move left
        direction = 2;
        moveBy(-10, 0);
    } else if ((event->key() == Qt::Key_Right)) {   //move right
        direction = 1;
        moveBy(10, 0);
    }

}

void FireBoy::jump(int jumpStep) {
    if (jumpStep < 14) {                 //part 1: upwards arc of jump
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
            upLevel = true;


        if (hitCeiling())
        {
            moveBy(0, 7.5);                  //move down 1 jumpStep
            jumpStep = 14;                   //fast track to part 2
        }

        if (hitPavement())
        {
            jumpStep = 14;                   //fast track to last else if statement
        }

        if (hitSide())
        {
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
        if (!upLevel)
        {
            switch (direction){
            case 0:
                moveBy(0, 7.5);
                break;
            case 1:
                moveBy(13.5, 7.5);
                break;
            case 2:
                moveBy(-13.5, 7.5);
                break ;
            }
        }else if (upLevel)  //if didn't hit ceiling in pt 1 then it must be going up a level and hence we ewant it's part 2 to not go too right or left do it has a less moveby x component then notuplevel
        {
            switch (direction){
            case 0:
                moveBy(0, 7.5);
                break;
            case 1:
                moveBy(5, 7.5);
                break;
            case 2:
                moveBy(-5, 7.5);
                break ;
            }
        }

        if (hitSide())
        {   //qDebug() << "Hit side";
            if (direction == 1)
                moveBy(-13.5, 0);         //move back 1 jumpStep
            else if (direction ==2)
                moveBy(13.5, 0);           //move back 1 jumpStep

            direction = 0;              //change direction so fall of jump can be straight dowwards
        }

        if (hitPavement())              //if hit pavement: end jump and return
        {
            //qDebug() << "end jump";
            if(hitCeiling())
                moveBy(0, -12);
            isJumping = false;
            gravity();
            return;
        } else                          //else if still in the air call Jump again (jumpstep is already 5 so it will keep calling part 2 untill it reaches condition and returns
            QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });

    }else if (hitPavement())              //if hit pavement: end jump and return
    {
       // qDebug() << "end jump";
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

    //Specific trouble spots
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
}


