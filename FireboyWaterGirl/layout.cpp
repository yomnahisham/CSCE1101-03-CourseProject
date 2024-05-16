#include "layout.h"
#include "allusers.h"
#include "status.h"
#include "obstacles.h"
#include "players.h"
#include "fireboy.h"
#include "watergirl.h"
#include "windowmanager.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>

Layout::Layout(QObject* parent, int l, User* loggedUser) : QGraphicsScene(parent), user(loggedUser) {
    //putting brick background
    level = l;
    nScore = 0;

    if (user)
        qDebug()<< user->username;
    else
        qDebug()<<"failed to transfer user";

    QGraphicsPixmapItem* brick = new QGraphicsPixmapItem();
    brick -> setPixmap(QPixmap(":/image/img/background.png").scaled(1000,800, Qt::KeepAspectRatio));
    brick-> setPos(0,0);
    addItem(brick);

    switch (l){
    case 1:
        baseLevel();
        break;
    case 2:
        baseLevel();
        makeLevelTWO();
        break;
    case 3:
        baseLevel();
        makeLevelTHREE();
        break;
    case 4:
        makeLevelFOUR();
        break;
    case 5:
        makeLevelFIVE();
        break;
    }

    FireBoy* firePlayer = new FireBoy();
    firePlayer->setPos(50, 658);
    addItem(firePlayer);

    WaterGirl* waterPlayer = new WaterGirl();
    waterPlayer->setPos(100, 658);
    addItem(waterPlayer);

}

void Layout::keyPressEvent(QKeyEvent* event) {
    QList<QGraphicsItem*> itemsList = items();              //create a list of items of qgraohics items
    for (QGraphicsItem* item : itemsList) {                 //for each item on list

    Players* player = dynamic_cast<Players*>(item);     //check if tyoe is of type player
        if (player)                                         //if dynamic cast does not make player a null ptr
            player->keyPressEvent(event);                  //call function key press event in player wich will be overriden for WaterGirl and FireBoy
    }
}

void Layout::baseLevel(){
    lever = 0;

    Obstacles* side = new Obstacles();
    side->createObstacle(Obstacles::Side);
    side -> setPixmap(QPixmap (":/image/img/Level1Side.png").scaled(1000, 800, Qt::KeepAspectRatio));
    side-> setPos(0, 0);
    addItem(side);

    Obstacles* c = new Obstacles();
    c->createObstacle(Obstacles::Ceiling);
    c -> setPixmap(QPixmap(":/image/img/level1c.png").scaled (1000,800, Qt::KeepAspectRatio));
    c -> setPos(0,0);
    addItem(c);

    Obstacles* Pav = new Obstacles();
    Pav->createObstacle(Obstacles::Pavement);
    Pav->setPixmap(QPixmap (":/image/img/level1pave.png").scaled(1000, 800, Qt::KeepAspectRatio));
    Pav-> setPos(0, 0);
    addItem(Pav);

    QGraphicsPixmapItem* l = new QGraphicsPixmapItem();
    l -> setPixmap(QPixmap(":/image/img/level1F.png").scaled(1000,800, Qt::KeepAspectRatio));
    l -> setPos(0,0);
    addItem(l);


    Obstacles* Gem1 = new Obstacles();
    Gem1->createObstacle(Obstacles::Gem);
    Gem1->setPos(348, 710);
    addItem(Gem1);
    obList.append(Gem1);

    Obstacles* Gem2 = new Obstacles();
    Gem2->createObstacle(Obstacles::Gem);
    Gem2->setPos(850, 710);
    addItem(Gem2);
    obList.append(Gem2);

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
    tacid-> setPos(210,578);
    addItem(tacid);
    obList.append(tacid);

    //add Block
    Obstacles* block = new Obstacles();
    block -> createObstacle(Obstacles::Block);
    block -> setPos(156,235);
    addItem (block);
    obList.append(block);

    //add WaterDoor
    Obstacles* WD = new Obstacles();
    WD -> createObstacle(Obstacles::WaterDoor);
    //WD -> setPos(893,80);
    WD-> setPos(150,658);
    addItem (WD);
    obList.append(WD);

    //add FireDoor
    Obstacles* FD = new Obstacles();
    FD -> createObstacle(Obstacles::FireDoor);
    //FD -> setPos(789,80);
    FD -> setPos(200,658);
    addItem (FD);
    obList.append(FD);

    Obstacles* redGem = new Obstacles();
    redGem->createObstacle(Obstacles::Gem);
    redGem->setPos(920, 140);
    addItem(redGem);
    obList.append(redGem);

    Obstacles* redGem2 = new Obstacles();
    redGem2->createObstacle(Obstacles::Gem);
    redGem2->setPos(810, 140);
    addItem(redGem2);
    obList.append(redGem2);
}


void Layout::makeLevelTWO(){
    Obstacles* acid2 = new Obstacles();
    acid2->createObstacle(Obstacles::Acid);
    acid2-> setPos(600,150);
    addItem(acid2);
    obList.append(acid2);

    Obstacles* fire2 = new Obstacles();
    fire2->createObstacle(Obstacles::Fire);
    fire2-> setPos(428, 400);
    addItem(fire2);
    obList.append(fire2);

    Obstacles* water2 = new Obstacles();
    water2->createObstacle(Obstacles::Water);
    water2-> setPos(630, 400);
    addItem(water2);
    obList.append(water2);

}

void Layout::shootAcid(int x, int y)
{
    Obstacles* acidBall = new Obstacles();
    acidBall->createObstacle(Obstacles::acidBall);
    acidBall-> setPos(x,y);
    addItem(acidBall);
}

void Layout::makeLevelTHREE(){

    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        shootAcid(400, 180);
        shootAcid(200, 600);
        shootAcid(650, 340);

    });    timer->start(2000);

}

void Layout::makeLevelFOUR(){

}

void Layout::makeLevelFIVE(){

}

void Layout::closeGame(QGraphicsScene* scene){
    QList<QGraphicsView *> views = scene->views();
    for (QGraphicsView *view : views) {
        view->close();
    }
}

void Layout::closeGame(){
    QList<QGraphicsView *> views = this -> views();
    for (QGraphicsView *view : views) {
        view->close();
    }
}

void Layout::handleCollisions(Players *player, Obstacles* ob)
{
    WindowManager Manager;

    // Check if the obstacle collides with the player
    if (ob->collidesWithItem(player)) {
        // Check if the player is a Fireboy or Watergirl
        FireBoy* fireboy = dynamic_cast<FireBoy*>(player);
        WaterGirl* watergirl = dynamic_cast<WaterGirl*>(player);

        if (fireboy) {
            if (wd)
                player->setZValue(1);

            if (ob->objectName() == "Water") {
                fireboy->kill();
                Manager.showWindow(WindowManager::over, level);
                closeGame(this);
            } else if (ob->objectName() == "Acid") {
                fireboy->kill();
                Manager.showWindow(WindowManager::over, level);
                closeGame(this);
            } else if (ob->objectName() == "FireDoor") {
                fd = true;
                Obstacles* openFDoor = new Obstacles();
                openFDoor->createObstacle(Obstacles::openFD);
                openFDoor->setPos(789, 80);
                addItem(openFDoor);
                player->setZValue(1);
            } else if (ob->objectName() == "Gem") {
                removeItem(ob);
                nScore += 100;
            }
        }

        if (watergirl) {
            if (fd)
                player->setZValue(1);

            if (ob->objectName() == "Fire") {
                watergirl->kill();
                Manager.showWindow(WindowManager::over, level);
                closeGame(this);
            } else if (ob->objectName() == "Acid") {
                watergirl->kill();
                Manager.showWindow(WindowManager::over, level);
                closeGame(this);
            } else if (ob->objectName() == "WaterDoor") {
                wd = true;
                Obstacles* openWDoor = new Obstacles();
                openWDoor->createObstacle(Obstacles::openWD);
                openWDoor->setPos(893, 80);
                addItem(openWDoor);
                player->setZValue(1);
            } else if (ob->objectName() == "Gem") {
                removeItem(ob);
                nScore += 100;
            }
        }
    }

    if (endgame)
    {
        wd = false;
        fd = false;
    }

    if (wd && fd) {
        endgame = true;
        qDebug()<< "entered if again";
        //QString username = user->username;
        AllUsers::updateScore(user, nScore);
        qDebug()<< "set won";
        Manager.WonGame(true);
        qDebug()<< "show window";
        Manager.showWindow(WindowManager::over, level, user);
        qDebug()<< "close";
        closeGame(this);
    }
}




