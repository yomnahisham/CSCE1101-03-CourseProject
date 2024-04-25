#include "layout.h"
#include "obstacles.h"
#include "players.h"
#include "fireboy.h"
#include "watergirl.h"
#include "windowmanager.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>

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
    lever = 0;
    QGraphicsPixmapItem* l = new QGraphicsPixmapItem();
    l -> setPixmap(QPixmap(":/image/img/level1Final.png").scaled(1000,800, Qt::KeepAspectRatio));
    l -> setPos(0,0);
    addItem(l);

    Obstacles* side = new Obstacles();
    side->createObstacle(Obstacles::Side);
    side -> setPixmap(QPixmap (":/image/img/Level1Side.png").scaled(1000, 800, Qt::KeepAspectRatio));
    side-> setPos(0, 0);
    addItem(side);

    Obstacles* slope = new Obstacles();
    slope->createObstacle(Obstacles::Slope);
    slope -> setPixmap(QPixmap(":/image/img/levelSlopes.png").scaled (1000,800, Qt::KeepAspectRatio));
    slope -> setPos(0,0);
    addItem(slope);

    Obstacles* c = new Obstacles();
    c->createObstacle(Obstacles::Ceiling);
    c -> setPixmap(QPixmap(":/image/img/level1Ceiling.png").scaled (1000,800, Qt::KeepAspectRatio));
    c -> setPos(0,0);
    addItem(c);

    Obstacles* Pav = new Obstacles();
    Pav->createObstacle(Obstacles::Pavement);
    Pav->setPixmap(QPixmap (":/image/img/level1Pav.png").scaled(1000, 800, Qt::KeepAspectRatio));
    Pav-> setPos(0, 0);
    addItem(Pav);

    //add fire pit
    Obstacles* fire = new Obstacles();
    fire->createObstacle(Obstacles::Fire);
    fire-> setPos(448, 710);
    addItem(fire);
    obList.append(fire);

    //add water
    Obstacles* water = new Obstacles();
    water->createObstacle(Obstacles::Water);
    water-> setPos(650, 715);
    addItem(water);
    obList.append(water);

    //add acid
    Obstacles* acid = new Obstacles();
    acid->createObstacle(Obstacles::Acid);
    acid-> setPos(600, 568);
    addItem(acid);
    obList.append(acid);

    Obstacles* tacid = new Obstacles();
    tacid->createObstacle(Obstacles::tinyAcid);
    tacid-> setPos(210,528);
    addItem(tacid);
    obList.append(tacid);

    //add jumping block above sliding floor 1
    Obstacles* jblock = new Obstacles();
    jblock -> createObstacle(Obstacles::Block);
    jblock -> setPos(23,475);
    addItem (jblock);
    obList.append(jblock);

    //add Block
    Obstacles* block = new Obstacles();
    block -> createObstacle(Obstacles::Block);
    block -> setPos(156,245);
    addItem (block);
    obList.append(block);

    Obstacles* ablock = new Obstacles();
    ablock -> createObstacle(Obstacles::Block);
    ablock -> setPos(920,372);
    addItem (ablock);
    obList.append(ablock);

    //add WaterDoor
    Obstacles* WD = new Obstacles();
    WD -> createObstacle(Obstacles::WaterDoor);
    WD -> setPos(893,80);
    addItem (WD);
    obList.append(WD);

    //add FireDoor
    Obstacles* FD = new Obstacles();
    FD -> createObstacle(Obstacles::FireDoor);
    FD -> setPos(789,80);
    addItem (FD);
    obList.append(FD);
}

void Layout::closeGame(QGraphicsScene* scene){
    QList<QGraphicsView *> views = scene->views();
    for (QGraphicsView *view : views) {
        view->close();
    }}

void Layout::closeGame(){
    QList<QGraphicsView *> views = this -> views();
    for (QGraphicsView *view : views) {
        view->close();
    }
}

void Layout::handleCollisions(Players *player, Obstacles* ob)
{
    bool wd = false;
    bool fd = false;

    // check if the obstacle collides with the player
    if (ob->collidesWithItem(player)) {
        // check if the player is a Fireboy or Watergirl
        FireBoy* fireboy = dynamic_cast<FireBoy*>(player);
        WaterGirl* watergirl = dynamic_cast<WaterGirl*>(player);

        if (fireboy) {
            if (ob -> objectName() == "Water"){
                fireboy->kill();
                closeGame(this);
            }else if (ob -> objectName() == "Acid"){
                fireboy->kill();
                closeGame(this);
            }else if (ob -> objectName() == "FireDoor"){
                fd = true;
            }
        }
        if(watergirl){
            if (ob -> objectName() == "Fire"){
                watergirl->kill();
                closeGame(this);
            } else if (ob -> objectName() == "Acid"){
                watergirl->kill();
                closeGame(this);
            }else if (ob -> objectName() == "WaterDoor"){
                wd = true;
            }
        }
    }

    if (wd&&fd)
    {
        WindowManager Manager;
        Manager.WonGame(true);
        Manager.showWindow(WindowManager::over);
        closeGame(this);
    }
}
