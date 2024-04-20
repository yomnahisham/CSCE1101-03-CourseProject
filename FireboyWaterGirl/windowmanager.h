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
    void transferLevel (int n);
private:
    WindowType type;
    int l; //level

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


#endif // WINDOWMANAGER_H
