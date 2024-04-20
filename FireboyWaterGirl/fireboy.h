#ifndef FIREBOY_H
#define FIREBOY_H

#include "Players.h"
#include <QKeyEvent>

class FireBoy : public Players {
    Q_OBJECT

public:
    FireBoy(QGraphicsItem* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
    void boundries() override;
    void kill() override;

private:
    void jump(int jumpStep);
    int direction;
    bool right, left = true;
    bool isJumping = false;
    int jumpStep;
    int originalY;
};

#endif // FIREBOY_H
