#include "windowmanager.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "level.h"
#include "fireboy.h"
#include "watergirl.h"
#include "layout.h"

bool WindowManager::loginON = false;
bool WindowManager::registerON = false;
bool WindowManager::levelON = false;
bool WindowManager::mainON = false;

RegisterWindow* WindowManager::registerWindow = new RegisterWindow();
LoginWindow* WindowManager::loginWindow = new LoginWindow();
QGraphicsView* WindowManager::view = new QGraphicsView();
Layout* WindowManager::scene = new Layout();

WindowManager::WindowManager(){

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

void WindowManager::showLoginWindow() {
    if(loginON)
        loginWindow->show();
    if (registerON == false)
        registerWindow->hide();
   // if (levelON == false)
       // levelWindow->hide();
    if (mainON == false)
        view->hide();
}

