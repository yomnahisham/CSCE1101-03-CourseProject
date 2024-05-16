#ifndef LAYOUT_H
#define LAYOUT_H
#include "players.h"
#include "obstacles.h"
#include <QGraphicsScene>
#include <QKeyEvent>

class Layout : public QGraphicsScene {
public:
    Layout(QObject* parent = nullptr, int lev = 0);
    void makeLevelONE();
    void makeLevelTWO();
    void makeLevelTHREE();
    void makeLevelFOUR();
    void makeLevelFIVE();

    void closeGame();
    void handleCollisions(Players *player, Obstacles* ob);
    static void closeGame(QGraphicsScene* scene);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    QList<Obstacles*> obList;
    int lever;
    bool wd = false;
    bool fd = false;
    int level;

};
#endif // LAYOUT_H

