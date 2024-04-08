#ifndef FIREBOY_H
#define FIREBOY_H

#include "Players.h"
#include <QKeyEvent>

class FireBoy : public Players {
    Q_OBJECT

public:
    FireBoy(QGraphicsItem* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;

private:
    void jump(int jumpStep);

    bool isJumping = false;
    int jumpStep;
    int originalY;

};

#endif // FIREBOY_H
