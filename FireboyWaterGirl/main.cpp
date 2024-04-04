#include "players.h"
#include "Fireboy.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsView * view = new QGraphicsView();
    view->setFixedSize(1000, 800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // creating scene
    QGraphicsScene * scene =  new QGraphicsScene() ;
    scene->setSceneRect(0, 0, 1000, 800);

    Players* Fire = new FireBoy();
    scene->addItem(Fire);

    // players->setPos(scene->width()/2, (200));

        // add scene ot view
        view->setScene(scene);
        view->show();

    return a.exec();
}
