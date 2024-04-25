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
    virtual void kill() = 0;
    void checkCollisions ();
protected:
    virtual void boundries() = 0;
    void gravity ();
    bool hitPavement();
    bool hitSide();
    bool hitSlope();
    bool hitCeiling();
    bool hitFloor();
    int originalY;

};

#endif // PLAYERS_H
