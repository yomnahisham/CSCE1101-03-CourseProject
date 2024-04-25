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
    void Leap(int Step, int height);


private:
    void jump(int jumpStep, int height);
    int direction;
    bool right, left = true;
    bool isJumping = false;
    int jumpStep;
};

#endif // FIREBOY_H
