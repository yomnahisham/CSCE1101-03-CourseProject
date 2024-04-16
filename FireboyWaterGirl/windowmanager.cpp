#include "windowmanager.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "level.h"
#include "fireboy.h"
#include "watergirl.h"
#include "layout.h"

bool loginON = false;
bool registerON = false;
bool levelON = false;
bool mainON = false;


RegisterWindow* registerWindow = new RegisterWindow();
LoginWindow* loginWindow = new LoginWindow();

QGraphicsView* view = new QGraphicsView();
Layout* scene = new Layout();


WindowManager::WindowManager(QObject *parent) : QObject(parent) {}


void WindowManager::start(){
    registerWindow->resize(1000, 500);
    loginWindow->resize(1000, 500);

    //loginWindow->show();
    // WindowManager::loginON = true;

    view->setFixedSize(1000, 800);
    view->setWindowTitle("Fire Boy & Water Girl");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(0, 0, 1000, 800);

    FireBoy* firePlayer = new FireBoy();
    firePlayer->setPos(100, 100);
    scene->addItem(firePlayer);

    WaterGirl* waterPlayer = new WaterGirl();
    waterPlayer->setPos(200, 200);
    scene->addItem(waterPlayer);

    view->setScene(scene);
    //view->show();
}

void WindowManager::showWindow(WindowType type) {
    switch (type){
    case login:
        loginON = true;
        break;
    case reg:
        registerON = true;
        break;
    case main:
        mainON = true;
    }

    if(loginON){
        loginWindow->show();
        registerWindow->hide();
        view->hide();
    } else if (registerON){
        loginWindow->hide();
        registerWindow->show();
        view->hide();
    } else if (mainON){
        loginWindow->hide();
        registerWindow->hide();
        view->show();
    }
}

