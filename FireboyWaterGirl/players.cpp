#include "Players.h"

Players::Players(QGraphicsItem* parent) : QGraphicsRectItem(parent) {}


//Players::~Players() {}

void Players::jump(){
    static int jumpStep = 0;
    if (jumpStep < jumpHeight) {
        moveBy(0, -5);
        jumpStep += 5;
    } else {
        jumpStep = 0;
    }
}
