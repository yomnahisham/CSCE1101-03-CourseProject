#include "layout.h"
#include "obstacles.h"
#include "players.h"

Layout::Layout(QObject* parent, int l) : QGraphicsScene(parent) {
    switch (l){
    case 1:
        Obstacles* pav = new Obstacles();
        pav->createObstacle(Obstacles::Pavement);
        pav-> setPos(0, 0);
        addItem(pav);

        //add fire pit
        Obstacles* fire = new Obstacles();
        fire->createObstacle(Obstacles::Fire);
        fire-> setPos(0, 0);
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
