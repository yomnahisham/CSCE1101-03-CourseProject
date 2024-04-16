#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QString>
#include "fireboy.h"
#include "watergirl.h"
#include "windowmanager.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    WindowManager::loginON=true;
    WindowManager::showLoginWindow();


    // check if username and password are valid, if so, allow show of view.


    //else if user pushes register, show register window and close login in window.
    // after registering, view->show()
    return app.exec();
}
