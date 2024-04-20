#ifndef FIREBOY_H
#define FIREBOY_H

#include "Players.h"
#include <QKeyEvent>

class FireBoy : public Players {
    Q_OBJECT

public:
    FireBoy(QGraphicsItem* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
    void boundries() override;
    void kill() override;
    double Pos[2]; // array for position with x and y
    double Velocity[2]; // velocity array in directions x and y
    double Acceleration; // acceleration in y (gravity effect)


private:
    void jump(int jumpStep, int height = 10);
    int direction;
    bool right, left = true;
    bool isJumping = false;
    int jumpStep;

    bool keyUpPressed;
    bool keyRightPressed;
    bool keyLeftPressed;
};

#endif // FIREBOY_H
/*int id1;
double x[2];
double y[2];
double vx[2];
double vy[2];
double ay[2];
double maxx[2];
double maxy[2];
double minx[2];
double miny[2];
int rednumber,bluenumber;
bool redget[4];
bool blueget[4];
int move_;
bool getMaxAndMin(int,int,int);
void reset();
~game();
protected:
void timerEvent(QTimerEvent *event);
private:
Ui::game *ui;
signals:
void winend1();
void loseend1();
void winend2();*/
