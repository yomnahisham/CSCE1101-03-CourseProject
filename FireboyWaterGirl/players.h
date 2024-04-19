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
    bool hitSide();
    virtual void boundries() = 0;
};

#endif // PLAYERS_H
