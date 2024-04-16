#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QGraphicsView>
#include "registerwindow.h"
#include "loginwindow.h"
#include "layout.h"

class WindowManager : public QObject {
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = nullptr);
    void start();

    enum WindowType{login, reg, main};
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
    Layout* scene;
};



    //static void showRegistrationWindow();
    //static void showLevelWindow();
    //static void showMainView();

   // static QWidget *loginWindow;
  //  static QWidget *registrationWindow;
 //   static QWidget *levelWindow;
    //static QGraphicsView *mainView;

#endif // WINDOWMANAGER_H
