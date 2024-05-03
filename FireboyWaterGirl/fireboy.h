#ifndef FIREBOY_H
#define FIREBOY_H

#include "players.h"
#include <QKeyEvent>

class FireBoy : public Players {
    Q_OBJECT

public:
    FireBoy(QGraphicsItem* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
    void boundries() override;
    void kill() override;
    bool atDoor();


private:
    void jump(int jumpStep);
    int direction;
    bool isJumping = false;
    int jumpStep;
    bool upLevel;
};

#endif // FIREBOY_H
