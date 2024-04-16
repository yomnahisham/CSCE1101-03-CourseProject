#ifndef STATUS_H
#define STATUS_H

#include <QGraphicsTextItem>

class Status
{
private:
    static int gems;
    static int score;
    static QGraphicsTextItem* gemsTextItem;
    static QGraphicsTextItem* scoreTextItem;
public:
    Status();
    static void setGemsText(QGraphicsTextItem* gemsTextItem);
    static void setScoreText(QGraphicsTextItem* scoreTextItem);
    static void increaseScore();
    static void increaseGems();
};


#endif // STATUS_H
