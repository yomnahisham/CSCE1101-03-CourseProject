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




WindowManager::WindowManager(QObject *parent) : QObject(parent) {}


void WindowManager::startLogin(){

    LoginWindow* loginWindow = new LoginWindow();
    loginWindow->resize(1000, 500);
    loginWindow->show();
    WindowManager::loginON = true;

}

void WindowManager::showWindow(WindowType type, int level) {
    LoginWindow* loginWindow = new LoginWindow();
    loginWindow->resize(1000, 500);

    RegisterWindow* registerWindow = new RegisterWindow();
    registerWindow->resize(1000, 500);

    Level* levWindow = new Level();
    levWindow->resize(1000, 500);

    switch (type){
    case login:
        loginON = true;
        registerON = false;
        levelON = false;
        mainON = false;
        break;
    case reg:
        registerON = true;
        loginON = false;
        levelON = false;
        mainON = false;
        break;
    case lev:
        levelON = true;
        registerON = false;
        loginON = false;
        mainON = false;
        break;
    case main: // game main window
        mainON = true;
        registerON = false;
        levelON = false;
        loginON = false;

    }    

    if(loginON){
        loginWindow->show();
        registerWindow->hide();
        levWindow -> hide();

    } else if (registerON){
        loginWindow->hide();
        levWindow -> hide();
        registerWindow -> show();

    } else if (levelON){
        loginWindow->hide();
        registerWindow->hide();
        levWindow -> show();

    }else if (mainON){
        //hiding other windows
        loginWindow->hide();
        registerWindow->hide();
        levWindow -> hide();


        QGraphicsView* view = new QGraphicsView();
        Layout* scene = new Layout();

        // setting up scene to start game
        view->setFixedSize(1000, 800);
        view->setWindowTitle("Fire Boy & Water Girl");
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene->setSceneRect(0, 0, 1000, 800);

        //adding players to scene
        FireBoy* firePlayer = new FireBoy();
        firePlayer->setPos(100, 100);
        scene->addItem(firePlayer);

        WaterGirl* waterPlayer = new WaterGirl();
        waterPlayer->setPos(200, 200);
        scene->addItem(waterPlayer);

        //setting up layout

        //setting background

        //adding scene to voew and showing it
        view->setScene(scene);
        view->show();
    }
}

