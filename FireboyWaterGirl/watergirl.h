#ifndef WATERGIRL_H
#define WATERGIRL_H

#include "Players.h"

class WaterGirl : public Players {
public:
    WaterGirl(QGraphicsItem* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;

private:
    void jump(int jumpStep);

    bool isJumping = false;
    int jumpStep;
    int originalY;
};

#endif // WATERGIRL_H
