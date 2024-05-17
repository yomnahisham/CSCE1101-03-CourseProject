#include "windowmanager.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "level.h"
#include "gameover.h"
#include "layout.h"

#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


WindowManager::WindowManager(QObject *parent) : QObject(parent) { won = false; }

void WindowManager::startLogin(){
    // starts login
    LoginWindow* loginWindow = new LoginWindow();
    loginWindow->resize(1000, 500);
    loginWindow->show();
    loginON = true;
}

void WindowManager::showWindow(WindowType type, int l, User* loggedUser) {
    // shows window based on bool

    user = loggedUser;

    switch (type){
    case login:
        loginON = true;
        registerON = false;
        levelON = false;
        mainON = false;
        overON = false;
        break;
    case reg:
        registerON = true;
        loginON = false;
        levelON = false;
        mainON = false;
        overON = false;
        break;
    case lev:
        levelON = true;
        registerON = false;
        loginON = false;
        mainON = false;
        overON = false;
        break;
    case main: // game main window
        mainON = true;
        registerON = false;
        levelON = false;
        loginON = false;
        overON = false;
        break;
    case over:
        mainON = false;
        registerON = false;
        levelON = false;
        loginON = false;
        overON = true;
        break;
    }

    if(loginON){
        LoginWindow* loginWindow = new LoginWindow();
        loginWindow->resize(1000, 500);
        loginWindow->show();

    } else if(registerON){
        RegisterWindow* registerWindow = new RegisterWindow();
        registerWindow->resize(1000, 500);
        registerWindow -> show();

    } else if(levelON){
        Level* levWindow = new Level(nullptr, user);
        levWindow->resize(500, 300);
        levWindow -> show();

    } else if(mainON){
        QGraphicsView* view = new QGraphicsView();
        Layout* scene = new Layout(nullptr, l, user);

        if (l == 1)
        {
            QDialog dialog(view);
            dialog.setWindowTitle("Level Information");

            QVBoxLayout layout(&dialog);
            QLabel infoLabel(&dialog);
            infoLabel.setText("This is level 1 of Fire Boy & Water Girl. This will teach you the basics of how to move around \n"
                              "         Controls for Water Girl: \n"
                              "             Press A for left, W for jump, D for right, \n "
                              "             E and Q to leap above puddles. \n"
                              "             and for going up floors you can press W then A or D dependning \n"
                              "             on the direction you want \n\n"
                              "         Controls for Fire Boy: \n"
                              "             Press Left Arrow for left, Up Arrow for jump, Right Arrow for right,  \n"
                              "             / and Shift to leap above puddles. \n"
                              "             and for going up floors you can press Up then Right or Left dependning \n"
                              "             on the direction you want \n\n"
                              "                                 Enjoy playing!");
            infoLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
            layout.addWidget(&infoLabel);

            QPushButton closeButton("Close", &dialog);
            layout.addWidget(&closeButton);

            QObject::connect(&closeButton, &QPushButton::clicked, &dialog, &QDialog::close);

            dialog.exec();
        }else if (l==2)
        {
            QDialog dialog(view);
            dialog.setWindowTitle("Level Information");

            QVBoxLayout layout(&dialog);
            QLabel infoLabel(&dialog);
            infoLabel.setText("                 This is level 2 of Fire Boy & Water Girl. \n"
                              "         Controls for Water Girl: \n"
                              "             Press A for left, W for jump, D for right, \n "
                              "             E and Q to leap above puddles. \n"
                              "             and for going up floors you can press W then A or D dependning \n"
                              "             on the direction you want \n\n"
                              "         Controls for Fire Boy: \n"
                              "             Press Left Arrow for left, Up Arrow for jump, Right Arrow for right,  \n"
                              "             / and Shift to leap above puddles. \n"
                              "             and for going up floors you can press Up then Right or Left dependning \n"
                              "             on the direction you want \n\n"
                              "                                 Enjoy playing!");
            infoLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
            layout.addWidget(&infoLabel);

            QPushButton closeButton("Close", &dialog);
            layout.addWidget(&closeButton);

            QObject::connect(&closeButton, &QPushButton::clicked, &dialog, &QDialog::close);

            dialog.exec();
        }else if (l==3)
        {
            QDialog dialog(view);
            dialog.setWindowTitle("Level Information");

            QVBoxLayout layout(&dialog);
            QLabel infoLabel(&dialog);
            infoLabel.setText("                 This is level 3 of Fire Boy & Water Girl. \n"
                              "         The goal of this level is to avoid the puddles and be carefull \n"
                              "                 of the acid balls falling at particular spots \n"
                              "                                 Enjoy playing!");
            infoLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
            layout.addWidget(&infoLabel);

            QPushButton closeButton("Close", &dialog);
            layout.addWidget(&closeButton);

            QObject::connect(&closeButton, &QPushButton::clicked, &dialog, &QDialog::close);

            dialog.exec();
        }else if (l==4)
        {
            QDialog dialog(view);
            dialog.setWindowTitle("Level Information");

            QVBoxLayout layout(&dialog);
            QLabel infoLabel(&dialog);
            infoLabel.setText("                 This is level 4 of Fire Boy & Water Girl. \n"
                              "         The goal of this level is to avoid the landmine puddles that can appear \n"
                              "         randomly and at any time, while also being careful of the acid balls \n"
                              "                                 Enjoy playing!");
            infoLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
            layout.addWidget(&infoLabel);

            QPushButton closeButton("Close", &dialog);
            layout.addWidget(&closeButton);

            QObject::connect(&closeButton, &QPushButton::clicked, &dialog, &QDialog::close);

            dialog.exec();
        }else if (l==5)
        {
            QDialog dialog(view);
            dialog.setWindowTitle("Level Information");

            QVBoxLayout layout(&dialog);
            QLabel infoLabel(&dialog);
            infoLabel.setText("                 This is level 5 of Fire Boy & Water Girl. \n"
                              "         Water droplets will start falling over the whole course, \n"
                              "         so be carefull of FireBiy's Health. To save him Water girl \n"
                              "         must reach the lever to close it off. Don't forget about the \n"
                              "                         landmine puddeles though\n"
                              "                                 Enjoy playing!");
            infoLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
            layout.addWidget(&infoLabel);

            QPushButton closeButton("Close", &dialog);
            layout.addWidget(&closeButton);

            QObject::connect(&closeButton, &QPushButton::clicked, &dialog, &QDialog::close);

            dialog.exec();
        }

        // setting up scene to start game
        view->setFixedSize(1000, 800);
        view->setWindowTitle("Fire Boy & Water Girl");
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene->setSceneRect(0, 0, 1000, 800);

        //adding scene to voew and showing it
        view->setScene(scene);
        view->show();

    } else if(overON){
        GameOver* gameover = new GameOver(nullptr, l, won, user);
        gameover->resize(500, 500);
        qDebug()<< "showing game over";
        gameover -> show();
    }
}

void WindowManager::WonGame(bool i)
{
    won = i;
}


