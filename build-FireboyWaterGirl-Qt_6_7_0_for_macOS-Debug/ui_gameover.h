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
    QPushButton *exitButton;
    QPushButton *checkLevelsButton;
    QLabel *gameOver;
    QLabel *wonLabel;

    void setupUi(QDialog *GameOver)
    {
        if (GameOver->objectName().isEmpty())
            GameOver->setObjectName("GameOver");
        GameOver->resize(916, 644);
        retryButton = new QPushButton(GameOver);
        retryButton->setObjectName("retryButton");
        retryButton->setGeometry(QRect(149, 220, 201, 32));
        exitButton = new QPushButton(GameOver);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(150, 320, 201, 32));
        checkLevelsButton = new QPushButton(GameOver);
        checkLevelsButton->setObjectName("checkLevelsButton");
        checkLevelsButton->setGeometry(QRect(150, 260, 201, 32));
        gameOver = new QLabel(GameOver);
        gameOver->setObjectName("gameOver");
        gameOver->setGeometry(QRect(210, 140, 211, 61));
        wonLabel = new QLabel(GameOver);
        wonLabel->setObjectName("wonLabel");
        wonLabel->setGeometry(QRect(220, 190, 58, 16));

        retranslateUi(GameOver);

        QMetaObject::connectSlotsByName(GameOver);
    } // setupUi

    void retranslateUi(QDialog *GameOver)
    {
        GameOver->setWindowTitle(QCoreApplication::translate("GameOver", "Dialog", nullptr));
        retryButton->setText(QCoreApplication::translate("GameOver", "Retry", nullptr));
        exitButton->setText(QCoreApplication::translate("GameOver", "Exit", nullptr));
        checkLevelsButton->setText(QCoreApplication::translate("GameOver", "Check Levels", nullptr));
        gameOver->setText(QCoreApplication::translate("GameOver", "Game Over!", nullptr));
        wonLabel->setText(QCoreApplication::translate("GameOver", "You Won!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameOver: public Ui_GameOver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVER_H
