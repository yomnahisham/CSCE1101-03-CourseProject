#ifndef FIREBOY_H
#define FIREBOY_H

#include "Players.h"
#include <QKeyEvent>

class FireBoy : public Players {
    Q_OBJECT

public:
    FireBoy(QGraphicsItem* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event);

private:
    void jump(int jumpStep, int direction);

    bool isJumping = false;
    int jumpStep;
    int originalY;
    bool upKey, rightKey, leftKey;

};

#endif // FIREBOY_H
