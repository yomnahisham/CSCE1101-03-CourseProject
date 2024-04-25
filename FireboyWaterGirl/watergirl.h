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
    void Leap(int Step, int height);

private:
    void jump(int jumpStep, int height = 10);
    bool isJumping = false;
    int jumpStep;
    int direction;
    bool right, left = true;
};

#endif // WATERGIRL_H
