 #include "windowmanager.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "level.h"

#include "layout.h"


WindowManager::WindowManager(QObject *parent) : QObject(parent) {}


void WindowManager::startLogin(){

    LoginWindow* loginWindow = new LoginWindow();
    loginWindow->resize(1000, 500);
    loginWindow->show();
    WindowManager::loginON = true;

}

void WindowManager::showWindow(WindowType type) {
    LoginWindow* loginWindow = new LoginWindow();
    loginWindow->resize(1000, 500);

    RegisterWindow* registerWindow = new RegisterWindow();
    registerWindow->resize(1000, 500);

    Level* levWindow = new Level();
    levWindow->resize(500, 300);

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
        Layout* scene = new Layout(nullptr, l);

        // setting up scene to start game
        view->setFixedSize(1000, 800);
        view->setWindowTitle("Fire Boy & Water Girl");
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene->setSceneRect(0, 0, 1000, 800);

        //adding players to scene


        //setting up layout

        //setting background

        //adding scene to voew and showing it
        view->setScene(scene);
        view->show();
    }
}

void WindowManager::transferLevel (int n)
{
    l = n;
}

