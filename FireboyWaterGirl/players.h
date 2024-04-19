#ifndef PLAYERS_H
#define PLAYERS_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Players : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Players(QGraphicsItem* parent = nullptr);
    virtual void keyPressEvent(QKeyEvent* event) = 0;
    void gravity ();
    bool hitPavement();
protected:
    int direction;
    bool right, left = true;
};

#endif // PLAYERS_H
