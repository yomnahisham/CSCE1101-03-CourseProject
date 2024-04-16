#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QWidget>
#include <QGraphicsView>

class WindowManager {
public:
    static void showLoginWindow();
    static void showRegistrationWindow();
    static void showLevelWindow();
    static void showMainView();

private:
    static QWidget *loginWindow;
    static QWidget *registrationWindow;
    static QWidget *levelWindow;
    static QGraphicsView *mainView;
};

#endif // WINDOWMANAGER_H
