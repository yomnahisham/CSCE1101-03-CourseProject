#include "layout.h"
#include "obstacles.h"
#include "players.h"
#include "fireboy.h"
#include "watergirl.h"
#include <QGraphicsPixmapItem>



Layout::Layout(QObject* parent, int l) : QGraphicsScene(parent) {
    //putting brick background
    QGraphicsPixmapItem* brick = new QGraphicsPixmapItem();
    brick -> setPixmap(QPixmap(":/image/img/background.png").scaled(1000,800, Qt::KeepAspectRatio));
    brick-> setPos(0,0);
    addItem(brick);

    QGraphicsPixmapItem* pav = new QGraphicsPixmapItem();

    switch (l){
    case 1:
        pav->setPixmap(QPixmap(":/image/img/level1Final.png").scaled(1000,800, Qt::KeepAspectRatio));
        pav-> setPos(0, 0);
        addItem(pav);

        //add fire pit
        Obstacles* fire = new Obstacles();
        fire->createObstacle(Obstacles::Fire);
        fire-> setPos(448, 715);
        addItem(fire);

        //add water
        Obstacles* water = new Obstacles();
        water->createObstacle(Obstacles::Water);
        water-> setPos(650, 715);
        addItem(water);

        //add acid
        Obstacles* acid = new Obstacles();
        acid->createObstacle(Obstacles::Acid);
        acid-> setPos(600, 568);
        addItem(acid);

        break;
    }

    FireBoy* firePlayer = new FireBoy();
    firePlayer->setPos(50, 657);
    addItem(firePlayer);

    qDebug()<<"Layout till water constructed";

    WaterGirl* waterPlayer = new WaterGirl();
    waterPlayer->setPos(50, 553);
    addItem(waterPlayer);
    /*waterPlayer->setScene(this);*/

}

void Layout::keyPressEvent(QKeyEvent* event) {
    QGraphicsScene::keyPressEvent(event);
    QList<QGraphicsItem*> itemsList = items();              //create a list of items of qgraohics items
    for (QGraphicsItem* item : itemsList) {                 //for each item on list
        Players* player = dynamic_cast<Players*>(item);     //check if tyoe is of type player
        if (player)                                         //if dynamic cast does not make player a null ptr
            player->keyPressEvent(event);                   //call function key press event in player wich will be overriden for WaterGirl and FireBoy
    }
}


