#ifndef PLAYERS_H
#define PLAYERS_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Players : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Players(QGraphicsItem* parent = nullptr);
    virtual void keyPressEvent(QKeyEvent* event) = 0;
    int jumpHeight = 10;

public slots:
    void jump();

//protected:
    //QTimer jumpTimer;


};

#endif // PLAYERS_H
