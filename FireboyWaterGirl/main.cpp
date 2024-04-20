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

    //window manager will start and it will manage all transitions between windows
    WindowManager windowManager;
    windowManager.startLogin();

    return app.exec();
}
