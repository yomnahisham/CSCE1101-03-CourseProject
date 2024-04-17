#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QGraphicsView>
#include "registerwindow.h"
#include "loginwindow.h"
#include "layout.h"
#include "level.h"

class WindowManager : public QObject {
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = nullptr);
    void startLogin();

    enum WindowType{login, reg, lev, main};
    void showWindow(WindowType type);
private:
    WindowType type;

    bool loginON;
    bool registerON;
    bool levelON;
    bool mainON;

    QGraphicsView* view;
    RegisterWindow* registerWindow;
    LoginWindow* loginWindow;
    Level* levWindow;
    Layout* scene;
};



    /*  Static idea → variables/functions that belong to all objects of a class and do not change from one object to the next
    static void showRegistrationWindow();
    static void showLevelWindow();
    static void showMainView();

    static QWidget *loginWindow;
    static QWidget *registrationWindow;
    static QWidget *levelWindow;
    static QGraphicsView *mainView;*/

#endif // WINDOWMANAGER_H
