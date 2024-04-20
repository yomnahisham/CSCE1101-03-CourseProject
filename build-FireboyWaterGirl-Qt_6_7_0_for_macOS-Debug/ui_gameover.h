/********************************************************************************
** Form generated from reading UI file 'gameover.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEOVER_H
#define UI_GAMEOVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GameOver
{
public:
    QPushButton *retryButton;
    QPushButton *leaderboardButton;
    QPushButton *exitButton;
    QPushButton *checkLevelsButton;
    QLabel *gameOver;

    void setupUi(QDialog *GameOver)
    {
        if (GameOver->objectName().isEmpty())
            GameOver->setObjectName("GameOver");
        GameOver->resize(813, 588);
        retryButton = new QPushButton(GameOver);
        retryButton->setObjectName("retryButton");
        retryButton->setGeometry(QRect(289, 270, 201, 32));
        leaderboardButton = new QPushButton(GameOver);
        leaderboardButton->setObjectName("leaderboardButton");
        leaderboardButton->setGeometry(QRect(290, 310, 201, 32));
        exitButton = new QPushButton(GameOver);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(290, 410, 201, 32));
        checkLevelsButton = new QPushButton(GameOver);
        checkLevelsButton->setObjectName("checkLevelsButton");
        checkLevelsButton->setGeometry(QRect(290, 350, 201, 32));
        gameOver = new QLabel(GameOver);
        gameOver->setObjectName("gameOver");
        gameOver->setGeometry(QRect(350, 190, 211, 61));

        retranslateUi(GameOver);

        QMetaObject::connectSlotsByName(GameOver);
    } // setupUi

    void retranslateUi(QDialog *GameOver)
    {
        GameOver->setWindowTitle(QCoreApplication::translate("GameOver", "Dialog", nullptr));
        retryButton->setText(QCoreApplication::translate("GameOver", "Retry", nullptr));
        leaderboardButton->setText(QCoreApplication::translate("GameOver", "View Leader Board", nullptr));
        exitButton->setText(QCoreApplication::translate("GameOver", "Exit", nullptr));
        checkLevelsButton->setText(QCoreApplication::translate("GameOver", "Check Levels", nullptr));
        gameOver->setText(QCoreApplication::translate("GameOver", "Game Over!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameOver: public Ui_GameOver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVER_H
