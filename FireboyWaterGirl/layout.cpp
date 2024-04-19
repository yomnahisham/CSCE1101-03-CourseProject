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

    Obstacles* Pav = new Obstacles();
    Pav->createObstacle(Obstacles::Pavement);

    Obstacles* side = new Obstacles();
    side->createObstacle(Obstacles::Side);


    switch (l){
    case 1:
        QPixmap si (":/image/img/Level1Side.png");
        side -> setPixmap(si.scaled(1000, 800, Qt::KeepAspectRatio));
        side-> setPos(0, 0);
        addItem(side);

        QPixmap p (":/image/img/level1Final.png");
        Pav->setPixmap(p.scaled(1000, 800, Qt::KeepAspectRatio));
        Pav-> setPos(0, 0);
        addItem(Pav);

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


