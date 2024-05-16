/********************************************************************************
** Form generated from reading UI file 'level.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEVEL_H
#define UI_LEVEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Level
{
public:
    QPushButton *Level1;
    QPushButton *level2B;
    QPushButton *level3B;
    QPushButton *level4B;
    QPushButton *level5B;

    void setupUi(QDialog *Level)
    {
        if (Level->objectName().isEmpty())
            Level->setObjectName("Level");
        Level->resize(525, 457);
        Level1 = new QPushButton(Level);
        Level1->setObjectName("Level1");
        Level1->setGeometry(QRect(190, 30, 100, 32));
        level2B = new QPushButton(Level);
        level2B->setObjectName("level2B");
        level2B->setGeometry(QRect(190, 80, 100, 32));
        level3B = new QPushButton(Level);
        level3B->setObjectName("level3B");
        level3B->setGeometry(QRect(190, 130, 100, 32));
        level4B = new QPushButton(Level);
        level4B->setObjectName("level4B");
        level4B->setGeometry(QRect(190, 180, 100, 32));
        level5B = new QPushButton(Level);
        level5B->setObjectName("level5B");
        level5B->setGeometry(QRect(190, 230, 100, 32));

        retranslateUi(Level);

        QMetaObject::connectSlotsByName(Level);
    } // setupUi

    void retranslateUi(QDialog *Level)
    {
        Level->setWindowTitle(QCoreApplication::translate("Level", "Dialog", nullptr));
        Level1->setText(QCoreApplication::translate("Level", "Level 1", nullptr));
        level2B->setText(QCoreApplication::translate("Level", "Level 2", nullptr));
        level3B->setText(QCoreApplication::translate("Level", "Level 3", nullptr));
        level4B->setText(QCoreApplication::translate("Level", "Level 4", nullptr));
        level5B->setText(QCoreApplication::translate("Level", "Level 5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Level: public Ui_Level {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVEL_H
