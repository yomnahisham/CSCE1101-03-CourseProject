#ifndef WATERGIRL_H
#define WATERGIRL_H
#include "layout.h"
#include "players.h"

class WaterGirl : public Players {
public:
    WaterGirl(QGraphicsItem* parent = nullptr);
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

#endif // WATERGIRL_H
