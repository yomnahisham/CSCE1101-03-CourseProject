#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QString>
#include "fireboy.h"
#include "watergirl.h"
#include "loginwindow.h"

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

void LoginClicked(QString name, QString pass){

}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);



    LoginWindow login;
    login.resize(1000, 500);
    login.show();


    // check if username and password are valid, if so, allow show of view.
    QGraphicsView * view = new QGraphicsView();
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

    //else if user pushes register, show register window and close login in window.
    // after registering, view->show()
    return app.exec();
}
