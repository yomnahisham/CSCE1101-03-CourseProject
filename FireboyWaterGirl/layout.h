#ifndef LAYOUT_H
#define LAYOUT_H
#include "players.h"
#include "obstacles.h"
#include "allusers.h"
#include "user.h"
#include <QGraphicsScene>
#include <QKeyEvent>

class Layout : public QGraphicsScene {
public:
    Layout(QObject* parent = nullptr, int lev = 0, User* loggedUser = nullptr, AllUsers* Allusers = nullptr);
    void baseLevel();
    void makeLevelTWO();
    void makeLevelTHREE();
    void makeLevelFOUR();
    void makeLevelFIVE();

    void closeGame();
    void handleCollisions(Players *player, Obstacles* ob);
    static void closeGame(QGraphicsScene* scene);

    User* user;
    AllUsers* allusers;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    QList<Obstacles*> obList;
    int lever;
    bool wd = false;
    bool fd = false;
    int level;
    void shootAcid (int x, int y);

    int nScore;
    int health = 1000;
    QGraphicsTextItem* healthText;

};
#endif // LAYOUT_H

