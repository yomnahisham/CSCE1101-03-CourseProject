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



    switch (l){
    case 1:
        makeLevelONE();
        break;
    }

    FireBoy* firePlayer = new FireBoy();
    firePlayer->setPos(50, 658);
    addItem(firePlayer);

    WaterGirl* waterPlayer = new WaterGirl();
    waterPlayer->setPos(50, 558);
    addItem(waterPlayer);

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

void Layout::makeLevelONE(){

    Obstacles* side = new Obstacles();
    side-> setObjectName("Side");
    side->createObstacle(Obstacles::Side);
    side -> setPixmap(QPixmap (":/image/img/Level1Side.png").scaled(1000, 800, Qt::KeepAspectRatio));
    side-> setPos(0, 0);
    addItem(side);

    Obstacles* slope = new Obstacles();
    slope-> setObjectName("Slope");
    slope->createObstacle(Obstacles::Slope);
    slope -> setPixmap(QPixmap(":/image/img/levelSlopes.png").scaled (1000,800, Qt::KeepAspectRatio));
    slope -> setPos(0,0);
    addItem(slope);

    Obstacles* c = new Obstacles();
    c-> setObjectName("Ceiling");
    c->createObstacle(Obstacles::Ceiling);
    c -> setPixmap(QPixmap(":/image/img/level1Ceiling.png").scaled (1000,800, Qt::KeepAspectRatio));
    c -> setPos(0,0);
    addItem(c);

    Obstacles* Pav = new Obstacles();
    Pav-> setObjectName("Pavement");
    Pav->createObstacle(Obstacles::Pavement);
    Pav->setPixmap(QPixmap (":/image/img/level1Final.png").scaled(1000, 800, Qt::KeepAspectRatio));
    Pav-> setPos(0, 0);
    addItem(Pav);

    //add fire pit
    Obstacles* fire = new Obstacles();
    fire->createObstacle(Obstacles::Fire);
    fire-> setPos(448, 710);
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

    //add lever
    Obstacles* lever = new Obstacles();
    lever -> createObstacle(Obstacles::LeverRight);
    lever -> setPos(210,485);
    addItem (lever);

    //add sliding Floor
    Obstacles* floor1 = new Obstacles();
    floor1 -> createObstacle(Obstacles::SlidingFloor1);
    floor1 -> setPos(20,402);
    addItem (floor1);

    //add button
    Obstacles* b1 = new Obstacles();
    b1 -> createObstacle(Obstacles::Button1);
    b1 -> setPos(251,382);
    addItem (b1);

    //add sliding Floor
    Obstacles* floor2 = new Obstacles();
    floor2 -> createObstacle(Obstacles::SlidingFloor2);
    floor2 -> setPos(870,300);
    addItem (floor2);

    //add button
    Obstacles* b2 = new Obstacles();
    b2 -> createObstacle(Obstacles::Button2);
    b2 -> setPos(755, 285);
    addItem (b2);

    //add Block
    Obstacles* block = new Obstacles();
    block -> createObstacle(Obstacles::Block);
    block -> setPos(570,200);
    addItem (block);

    //add WaterDoor
    Obstacles* WD = new Obstacles();
    WD -> createObstacle(Obstacles::WaterDoor);
    WD -> setPos(893,80);
    addItem (WD);

    //add FireDoor
    Obstacles* FD = new Obstacles();
    FD -> createObstacle(Obstacles::FireDoor);
    FD -> setPos(789,80);
    addItem (FD);
}

