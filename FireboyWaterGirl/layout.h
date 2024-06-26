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
    Layout(QObject* parent = nullptr, int lev = 0, User* loggedUser = nullptr);
    void baseLevel();
    void makeLevelTWO();
    void makeLevelTHREE();
    void makeLevelFOUR();
    void makeLevelFIVE();

    void handleCollisions(Players *player, Obstacles* ob);
    static void closeGame(QGraphicsScene* scene);

    User* user;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void shootAcid (int x, int y);
    void lostgame();

    int lever;
    bool wd = false;
    bool fd = false;
    int level;
    bool endgame = false;

    int nScore;
    int health = 1000;
    QGraphicsTextItem* healthText;

    QTimer* dropTimer;
    bool dropsSwitchedOff;

};
#endif // LAYOUT_H

