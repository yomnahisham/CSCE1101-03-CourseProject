#include "layout.h"
#include "allusers.h"
#include "obstacles.h"
#include "players.h"
#include "fireboy.h"
#include "watergirl.h"
#include "windowmanager.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>

Layout::Layout(QObject* parent, int l, User* loggedUser) : QGraphicsScene(parent), user(loggedUser) {
    //initalize variables
    level = l;
    nScore = 0;
    dropsSwitchedOff = false;

    //checking user is properly transfered
    if (user)
        qDebug()<< user->username;
    else
        qDebug()<<"failed to transfer user";


    //add background image of brickwall
    QGraphicsPixmapItem* brick = new QGraphicsPixmapItem();
    brick -> setPixmap(QPixmap(":/image/img/background.png").scaled(1000,800, Qt::KeepAspectRatio));
    brick-> setPos(0,0);
    addItem(brick);

    //switch case for each level
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
        baseLevel();
        makeLevelFOUR();
        break;
    case 5:
        baseLevel();
        makeLevelFIVE();
        break;
    }

    //add players to scene
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

    Players* player = dynamic_cast<Players*>(item);     //check if type is of type player
        if (player)                                         //if dynamic cast does not make player a null ptr
            player->keyPressEvent(event);                  //call function key press event in player wich will be overriden for WaterGirl and FireBoy
    }
}

void Layout::baseLevel(){

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

    Obstacles* Gem2 = new Obstacles();
    Gem2->createObstacle(Obstacles::Gem);
    Gem2->setPos(850, 710);
    addItem(Gem2);

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

    Obstacles* tacid = new Obstacles();
    tacid->createObstacle(Obstacles::tinyAcid);
    tacid-> setPos(210,578);
    addItem(tacid);

    //add Block
    Obstacles* block = new Obstacles();
    block -> createObstacle(Obstacles::Block);
    block -> setPos(156,235);
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

    Obstacles* redGem = new Obstacles();
    redGem->createObstacle(Obstacles::Gem);
    redGem->setPos(920, 140);
    addItem(redGem);

    Obstacles* redGem2 = new Obstacles();
    redGem2->createObstacle(Obstacles::Gem);
    redGem2->setPos(810, 140);
    addItem(redGem2);
}


void Layout::makeLevelTWO(){
    Obstacles* acid2 = new Obstacles();
    acid2->createObstacle(Obstacles::tinyAcid);
    acid2-> setPos(600,160);
    addItem(acid2);

    Obstacles* fire2 = new Obstacles();
    fire2->createObstacle(Obstacles::tinyFire);
    fire2-> setPos(428, 420);
    addItem(fire2);

    Obstacles* water2 = new Obstacles();
    water2->createObstacle(Obstacles::tinyWater);
    water2-> setPos(630, 420);
    addItem(water2);

}

void Layout::shootAcid(int x, int y)
{
    Obstacles* acidBall = new Obstacles();
    acidBall->createObstacle(Obstacles::acidBall);
    acidBall-> setPos(x,y);
    addItem(acidBall);
}

void Layout::makeLevelTHREE(){

    Obstacles* Gem1 = new Obstacles();
    Gem1->createObstacle(Obstacles::Gem);
    Gem1->setPos(400, 250);
    addItem(Gem1);

    Obstacles* Gem2 = new Obstacles();
    Gem2->createObstacle(Obstacles::Gem);
    Gem2->setPos(200, 670);
    addItem(Gem2);

    Obstacles* Gem3 = new Obstacles();
    Gem3->createObstacle(Obstacles::Gem);
    Gem3->setPos(50, 420);
    addItem(Gem3);

    QTimer * timer = new QTimer(this);          //creating acid balls useing a timer for different loactions
    connect(timer, &QTimer::timeout, [=]() {
        shootAcid(400, 180);
        shootAcid(200, 600);
        shootAcid(650, 340);
    });    timer->start(2000);

}

void Layout::makeLevelFOUR() {

    Obstacles* Gem1 = new Obstacles();
    Gem1->createObstacle(Obstacles::Gem);
    Gem1->setPos(690, 120);
    addItem(Gem1);

    Obstacles* Gem2 = new Obstacles();
    Gem2->createObstacle(Obstacles::Gem);
    Gem2->setPos(50, 470);
    addItem(Gem2);

    Obstacles* Gem3 = new Obstacles();
    Gem3->createObstacle(Obstacles::Gem);
    Gem3->setPos(50, 340);
    addItem(Gem3);

    Obstacles* Gem4 = new Obstacles();
    Gem4->createObstacle(Obstacles::Gem);
    Gem4->setPos(775, 250);
    addItem(Gem4);

    // possible positions for obstacles
    QVector<QPointF> positions = {
        {400, 573}, {600, 163}, {300, 290}
    };

    // function to randomly display an obstacle
    auto showRandomObstacle = [=](Obstacles::ObstacleType type) {
        Obstacles* obstacle = new Obstacles();
        obstacle->createObstacle(type);
        QPointF pos = positions[QRandomGenerator::global()->bounded(positions.size())];
        obstacle->setPos(pos);

        addItem(obstacle);
        obstacle->setVisible(true);

        QTimer::singleShot(1000, obstacle, [=]() {
            removeItem(obstacle);
            delete obstacle;
        });
    };

    // timers for random obstacles
    QTimer* randomObstacleTimer = new QTimer(this);
    connect(randomObstacleTimer, &QTimer::timeout, [=]() {
        int randomType = QRandomGenerator::global()->bounded(3);
        switch (randomType) {
        case 0:
            showRandomObstacle(Obstacles::tinyAcid);
            break;
        case 1:
            showRandomObstacle(Obstacles::tinyFire);
            break;
        case 2:
            showRandomObstacle(Obstacles::tinyWater);
            break;
        }
    });

    // start the timer with a random interval between 1 and 3 seconds
    randomObstacleTimer->start(1000 + QRandomGenerator::global()->bounded(2000));


    //acid balls
    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        shootAcid(775, 180);
        shootAcid(880, 600);
        shootAcid(100, 340);
    });    timer->start(2000);
}



void Layout::makeLevelFIVE(){
    lever = 0;  //initialize lever count to 0

    // insert a lever
    Obstacles* lever = new Obstacles();
    lever->createObstacle(Obstacles::LeverLeft);
    lever->setPos(600, 384);
    addItem(lever);

    // start timer for dropping drops
    dropTimer = new QTimer(this);
    connect(dropTimer, &QTimer::timeout, [=]() {
        if (!dropsSwitchedOff) {
            // create and add a drop at a random position
            Obstacles* drop = new Obstacles();
            drop->createObstacle(Obstacles::Drops);
            int x = QRandomGenerator::global()->bounded(30, 920);
            int y = 0;
            drop->setPos(x, y);
            addItem(drop);

            // start timer for moving drops downwards
            QTimer* dropMoveTimer = new QTimer(drop);
            connect(dropMoveTimer, &QTimer::timeout, [=]() { drop->moveBy(0, 5); });
            dropMoveTimer->start(50);
        }
    });
    dropTimer->start(500);

    // possible positions for obstacles
    QVector<QPointF> positions = {
        {400, 573}, {600, 163}, {300, 290}
    };

    // function to randomly display an obstacle
    auto showRandomObstacle = [=](Obstacles::ObstacleType type) {
        Obstacles* obstacle = new Obstacles();
        obstacle->createObstacle(type);
        QPointF pos = positions[QRandomGenerator::global()->bounded(positions.size())];
        obstacle->setPos(pos);

        addItem(obstacle);
        obstacle->setVisible(true);

        QTimer::singleShot(1000, obstacle, [=]() {
            removeItem(obstacle);
            delete obstacle;
        });
    };

    // timers for random obstacles
    QTimer* randomObstacleTimer = new QTimer(this);
    connect(randomObstacleTimer, &QTimer::timeout, [=]() {
        int randomType = QRandomGenerator::global()->bounded(3);
        switch (randomType) {
        case 0:
            showRandomObstacle(Obstacles::tinyAcid);
            break;
        case 1:
            showRandomObstacle(Obstacles::tinyFire);
            break;
        case 2:
            showRandomObstacle(Obstacles::tinyWater);
            break;
        }
    });

    // start the timer with a random interval between 1 and 3 seconds
    randomObstacleTimer->start(1000 + QRandomGenerator::global()->bounded(2000));
}

void Layout::closeGame(QGraphicsScene* scene){
    QList<QGraphicsView *> views = scene->views();
    for (QGraphicsView *view : views) {
        view->close();
    }
}

void Layout::handleCollisions(Players *player, Obstacles* ob)
{

    // check if the obstacle collides with the player
    if (ob->collidesWithItem(player) && !endgame) {
        // check if the player is a Fireboy or Watergirl
        FireBoy* fireboy = dynamic_cast<FireBoy*>(player);
        WaterGirl* watergirl = dynamic_cast<WaterGirl*>(player);

        if (fireboy) {
            if (wd)
                player->setZValue(1);   //bring player to front

            if (ob->objectName() == "Water") {
                fireboy->kill();
                lostgame();
            } else if (ob->objectName() == "Acid") {
                fireboy->kill();
                lostgame();
            } else if (ob->objectName() == "FireDoor") {
                fd = true;
                Obstacles* openFDoor = new Obstacles();
                openFDoor->createObstacle(Obstacles::openFD);
                openFDoor->setPos(789, 80);
                addItem(openFDoor);
                player->setZValue(1);//bring player to front
            } else if (ob->objectName() == "Gem") {
                removeItem(ob);
                nScore += 100;
            } else if (ob->objectName() == "Drops") {
                // update health text for Fireboy
                if (!healthText) {
                    healthText = new QGraphicsTextItem();
                    healthText->setDefaultTextColor(Qt::red);
                    healthText->setFont(QFont("times", 16));
                    healthText->setPos(50, 50); // Adjust position as needed
                    addItem(healthText);
                }
                // update health
                health -= 50;
                healthText->setPlainText("Health: " + QString::number(health));
                if (health <= 0) {
                    fireboy->kill();
                    lostgame();
                }
            }
        }

        if (watergirl) {
            if (fd)
                player->setZValue(1); //bring player to front

            if (ob->objectName() == "Fire") {
                watergirl->kill();
                lostgame();
            } else if (ob->objectName() == "Acid") {
                watergirl->kill();
                lostgame();
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
            } else if (ob->objectName() == "Drops"){
                // if a drop touches Watergirl, increase its descent speed
                QTimer* dropMoveTimer = dynamic_cast<QTimer*>(ob->parent());
                if (dropMoveTimer) {
                    dropMoveTimer->setInterval(15);
                }
            } else if (ob->objectName() == "LeverLeft"){
                Obstacles* switched = new Obstacles();
                switched->createObstacle(Obstacles::LeverRight);
                switched->setPos(ob->x(), ob->y());
                addItem(switched);
                removeItem(ob);

                dropsSwitchedOff = true;  // set the flag to true
                dropTimer->stop();  // stop the drop timer
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
        AllUsers::updateScore(user, nScore);
        WindowManager Manager;
        Manager.WonGame(true);
        Manager.showWindow(WindowManager::over, level, user);
        closeGame(this);
    }
}

void Layout::lostgame(){
    endgame = true;
    WindowManager Manager;
    Manager.showWindow(WindowManager::over, level, user);
    closeGame(this);
}




