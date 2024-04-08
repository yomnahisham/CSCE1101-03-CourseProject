#ifndef FIREBOY_H
#define FIREBOY_H

#include "Players.h"

class FireBoy : public Players {
public:
    FireBoy(QGraphicsItem* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // FIREBOY_H
