#include "fireboy.h"
#include "windowmanager.h"
#include <QBrush>
#include <QTimer>


FireBoy::FireBoy(QGraphicsItem* parent) : Players(parent) {
    setPixmap(QPixmap(":/image/img/FireBoy.png").scaled(50,70, Qt::KeepAspectRatio)); // fix scaling

    // set initial values of position, velocity, and acceleration
    Pos[0] = 50;
    Pos[1] = 658;

    Velocity[0] = 0;
    Velocity[1] = 0;

    Acceleration = 0;

    // set bool values for keypress
    keyUpPressed = false;
    keyLeftPressed = false;
    keyRightPressed = false;

}

void FireBoy::keyPressEvent(QKeyEvent* event) {
    // update bool values according to event
    switch(event->key()) {
    case Qt::Key_Up:
        keyUpPressed = true;
        break;
    case Qt::Key_Left:
        keyLeftPressed = true;
        break;
    case Qt::Key_Right:
        keyRightPressed = true;
        break;
    default:
        break;
    }

    int update[2] = {0, 0};
    if(keyUpPressed){
        update[1]++;
    }
    if(keyRightPressed){
        update[0]++;
    }
    if(keyLeftPressed){
        update[0]--;
    }

    // update velocity in x according to update[0]
    if(update[0]<0){
        Velocity[0]-=0.1;
        // set minimum velocity
        if(Velocity[0]<-1.5){
            Velocity[0] = -1.5;
        }
    } else if (update[0]>0){
        Velocity[0]+=0.1;
        // set maximum velocity
        if(Velocity[0]<1.5){
            Velocity[0] = 1.5;
        }
    } else Velocity[0]=0;

    // update velocity in y according to update[1]
    if(update[1]>0){
        if(Velocity[1]==0){
            Velocity[1]=2.5;
        }
        // need to check max and min of each part of the layout
        if(Velocity[1]==0){}


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
            jump (0, 10);
        }
        else
            moveBy(-10, 0);

    } else if ((event->key() == Qt::Key_Right)&&right) {
        direction = 1;
        if (isJumping){
            isJumping = false;
            jump (0, 10);
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
            moveBy(16, -height);
            break;
        case 2:
            moveBy(-16, -height);
            break ;
        }
        ++jumpStep;

        if (hitCeiling())                                                                          //if hit pavement at the top, start falling, skip to secind else if
        {
            qDebug()<< "hit ceiling";
            direction = 0;
            jumpStep = 5;
        }

        if (hitSide())                                                                              //if hit side go back down and skip to last else if
        {
            qDebug()<< "hit side";
            boundries();
            direction = 0;
        }

        if (hitSlope())
        {
            qDebug()<< "hit slope";
            boundries();
            setPos(x(), y());
            isJumping = false; // Reset isJumping flag
            return;
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
            moveBy(16, height);
            break;
        case 2:
            moveBy(-16, height);
            break ;
        }
        QTimer::singleShot(40, this, [this, jumpStep]() { jump(jumpStep); });
    }
    else if (hitPavement() && hitSlope()&& !hitCeiling()&&!hitSide())
    {
        qDebug()<< "jump done";
        setPos(x(), y());
        isJumping = false; // Reset isJumping flag
        return;
    }
}

void FireBoy::boundries()
{
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
