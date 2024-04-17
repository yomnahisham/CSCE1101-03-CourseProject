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

    void setupUi(QDialog *Level)
    {
        if (Level->objectName().isEmpty())
            Level->setObjectName("Level");
        Level->resize(534, 445);
        Level1 = new QPushButton(Level);
        Level1->setObjectName("Level1");
        Level1->setGeometry(QRect(200, 120, 100, 32));

        retranslateUi(Level);

        QMetaObject::connectSlotsByName(Level);
    } // setupUi

    void retranslateUi(QDialog *Level)
    {
        Level->setWindowTitle(QCoreApplication::translate("Level", "Dialog", nullptr));
        Level1->setText(QCoreApplication::translate("Level", "Level 1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Level: public Ui_Level {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEVEL_H
