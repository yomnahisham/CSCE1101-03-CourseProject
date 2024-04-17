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
        QGraphicsPixmapItem* pav = new QGraphicsPixmapItem();
        pav->setPixmap(QPixmap(":/image/img/level1Final.png").scaled(1000,800, Qt::KeepAspectRatio));
        pav-> setPos(0, 0);
        addItem(pav);

        //add fire pit
        Obstacles* fire = new Obstacles();
        fire->createObstacle(Obstacles::Fire);
        fire-> setPos(800, 600);
        addItem(fire);

        //add water
        Obstacles* water = new Obstacles();
        water->createObstacle(Obstacles::Water);
        water-> setPos(0, 0);
        addItem(water);

        //add acid
        Obstacles* acid = new Obstacles();
        acid->createObstacle(Obstacles::Acid);
        acid-> setPos(0, 0);
        addItem(acid);

        break;
    }

    FireBoy* firePlayer = new FireBoy();
    firePlayer->setPos(100, 100);
    addItem(firePlayer);

    WaterGirl* waterPlayer = new WaterGirl();
    waterPlayer->setPos(200, 200);
    addItem(waterPlayer);
}

void Layout::keyPressEvent(QKeyEvent* event) {
    QGraphicsScene::keyPressEvent(event);
    QList<QGraphicsItem*> itemsList = items();
    for (QGraphicsItem* item : itemsList) {
        Players* player = dynamic_cast<Players*>(item);
        if (player)
            player->keyPressEvent(event);
    }
}
