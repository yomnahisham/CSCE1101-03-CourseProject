#include "layout.h"
#include "obstacles.h"
#include "players.h"

Layout::Layout(QObject* parent, int l) : QGraphicsScene(parent) {

}

void Layout::keyPressEvent(QKeyEvent* event) {
    QGraphicsScene::keyPressEvent(event);
    QList<QGraphicsItem*> itemsList = items();
    for (QGraphicsItem* item : itemsList) {
        Players* player = dynamic_cast<Players*>(item);
        if (player)
            player->keyPressEvent(event);
    }
}
