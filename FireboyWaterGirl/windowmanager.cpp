#include "windowmanager.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "level.h"
#include "gameover.h"

#include "layout.h"


WindowManager::WindowManager(QObject *parent) : QObject(parent) {}

void WindowManager::gameDemo(){
    QGraphicsView* view = new QGraphicsView();
    Layout* scene = new Layout(nullptr, 1);

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
        overON = false;
        break;
    case reg:
        registerON = true;
        loginON = false;
        levelON = false;
        mainON = false;
        overON = false;
        break;
    case lev:
        levelON = true;
        registerON = false;
        loginON = false;
        mainON = false;
        overON = false;
        break;
    case main: // game main window
        mainON = true;
        registerON = false;
        levelON = false;
        loginON = false;
        overON = false;
        break;
    case over:
        mainON = false;
        registerON = false;
        levelON = false;
        loginON = false;
        overON = true;
        break;
    }

    if(loginON){
        LoginWindow* loginWindow = new LoginWindow();
        loginWindow->resize(1000, 500);
        loginWindow->show();

    } else if(registerON){
        RegisterWindow* registerWindow = new RegisterWindow();
        registerWindow->resize(1000, 500);
        registerWindow -> show();

    } else if(levelON){
        Level* levWindow = new Level();
        levWindow->resize(500, 300);
        levWindow -> show();

    } else if(mainON){

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
    } else if(overON){
        GameOver* gameover = new GameOver();
        gameover->resize(500, 500);
        gameover -> show();
    }
}

void WindowManager::endWindow(WindowType type){
    switch (type){
    case lev:
        levelON = false;
        registerON = false;
        loginON = false;
        mainON = false;
        overON = false;
        break;
    }
}

void WindowManager::transferLevel (int n)
{
    l = n;
}

