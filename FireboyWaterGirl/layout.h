#ifndef LAYOUT_H
#define LAYOUT_H

#include <QGraphicsScene>
#include <QKeyEvent>

class Layout : public QGraphicsScene {
public:
    Layout(QObject* parent = nullptr, int lev = 0);
    QGraphicsPixmapItem* pav;
protected:
    void keyPressEvent(QKeyEvent* event) override;

};
#endif // LAYOUT_H

