#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QGraphicsView>
#include "registerwindow.h"
#include "loginwindow.h"
//?? #include "layout.h"

class WindowManager {
public:
    static bool loginON;
    static bool registerON;
    static bool levelON;
    static bool mainON;

    WindowManager();
    static void showLoginWindow();

private:
    static RegisterWindow* registerWindow;
    static LoginWindow* loginWindow;
    static QGraphicsView* view;

    //static void showRegistrationWindow();
    //static void showLevelWindow();
    //static void showMainView();

   // static QWidget *loginWindow;
  //  static QWidget *registrationWindow;
 //   static QWidget *levelWindow;
    //static QGraphicsView *mainView;
};

#endif // WINDOWMANAGER_H
