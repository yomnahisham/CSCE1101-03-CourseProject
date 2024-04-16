#include "windowmanager.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "level.h"
#include "fireboy.h"
#include "watergirl.h"

bool WindowManager::loginON = false;
bool WindowManager::registerON = false;
bool WindowManager::levelON = false;
bool WindowManager::mainON = false;

RegisterWindow* registerWindow = new RegisterWindow();
LoginWindow* loginWindow = new LoginWindow();
QGraphicsView* view = new QGraphicsView();

WindowManager::WindowManager(){

    registerWindow->resize(1000, 500);


    loginWindow->resize(1000, 500);
    loginWindow->show();
    WindowManager::loginON = true;

    class Scene : public QGraphicsScene {
    public:
        Scene(QObject* parent = nullptr) : QGraphicsScene(parent) {}
    protected:
        void keyPressEvent(QKeyEvent* event) override {
            QList<QGraphicsItem*> players = items();
            for (QGraphicsItem* item : players) {
                Players* player = dynamic_cast<Players*>(item);
                if (player)
                    player->keyPressEvent(event);
            }
        }
    };


    view->setFixedSize(1000, 800);
    view->setWindowTitle("Fire Boy & Water Girl");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Scene scene;
    scene.setSceneRect(0, 0, 1000, 800);


    FireBoy firePlayer;
    firePlayer.setPos(100, 100); //edit later
    scene.addItem(&firePlayer);


    WaterGirl waterPlayer;
    waterPlayer.setPos(200, 200);//edit later
    scene.addItem(&waterPlayer);

    view->setScene(&scene);
    view->show();

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

