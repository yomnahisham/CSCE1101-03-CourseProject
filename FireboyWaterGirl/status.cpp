#include "status.h"

#include <QString>
#include <QMessageBox>
#include <QGraphicsScene>

// setting static member variables
int Status::gems = 3;
int Status::score = 0;
QGraphicsTextItem* Status::gemsTextItem = nullptr;
QGraphicsTextItem* Status::scoreTextItem = nullptr;

void Status::setGemsText(QGraphicsTextItem* gemsText) {
    // function to set to set health for initialization
    gemsTextItem = gemsText;
    gemsTextItem->setPlainText("Health: " + QString::number(gems));
    gemsTextItem->setPos(20, 30);
}

void Status::setScoreText(QGraphicsTextItem* scoreText){
    // function to set to set score for initialization
    scoreTextItem = scoreText;
    scoreTextItem->setPlainText("Score: " + QString::number(score));
    scoreTextItem->setPos(20, 50);
}

void Status::increaseScore() {
    // function to increase health by 100
    score += 100;
    // updating score
    scoreTextItem->setPlainText("Score: " + QString::number(score));
}

void Status::increaseGems(){
    //if collision from obstacle is collided with a gem, increase gems
    gems += 10;
    gemsTextItem->setPlainText("Score: " + QString::number(gems));
}

