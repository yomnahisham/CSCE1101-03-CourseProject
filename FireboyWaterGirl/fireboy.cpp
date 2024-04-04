#include "FireBoy.h"
#include <QGraphicsPixmapItem>


FireBoy::FireBoy() :QObject(), QGraphicsPixmapItem(QPixmap(":/img/PinkcChick .png").scaled(60, 70)) {
    setPos(100, 200);
}
