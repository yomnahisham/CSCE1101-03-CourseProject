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
    loginON = true;
}

void WindowManager::showWindow(WindowType type) {

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
        LoginWindow* loginWindow = new LoginWindow();
        loginWindow->resize(1000, 500);
        loginWindow->show();

    } else if (registerON){
        RegisterWindow* registerWindow = new RegisterWindow();
        registerWindow->resize(1000, 500);
        registerWindow -> show();

    } else if (levelON){
        Level* levWindow = new Level();
        levWindow->resize(500, 300);
        levWindow -> show();

    } else if (mainON){

        QGraphicsView* view = new QGraphicsView();
        Layout* scene = new Layout(nullptr, l);

        // setting up scene to start game
        view->setFixedSize(1000, 800);
        view->setWindowTitle("Fire Boy & Water Girl");
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene->setSceneRect(0, 0, 1000, 800);

        //adding scene to voew and showing it
        view->setScene(scene);
        view->show();
    }
}

void WindowManager::transferLevel (int n)
{
    l = n;
}

