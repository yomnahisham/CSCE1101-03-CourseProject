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
    void gameDemo();

    enum WindowType{login, reg, lev, main, over};
    void showWindow(WindowType type, int l = 0, User* loggedUser = nullptr, AllUsers* Allusers = nullptr);
    void endWindow(WindowType type);
    void transferLevel (int n);
    void WonGame(bool i);

private:
    WindowType type;
    int l; //level

    bool loginON;
    bool registerON;
    bool levelON;
    bool mainON;
    bool overON;
    bool won;

    QGraphicsView* view;
    RegisterWindow* registerWindow;
    LoginWindow* loginWindow;
    Level* levWindow;
    Layout* scene;
};


#endif // WINDOWMANAGER_H
