#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QWidget>
#include <QGraphicsView>

class WindowManager {
public:
    WindowManager();
    static void showLoginWindow();
    //static void showRegistrationWindow();
    //static void showLevelWindow();
    //static void showMainView();

private:
    static bool loginON;
    static bool registerON;
    static bool levelON;
    static bool mainON;

   // static QWidget *loginWindow;
  //  static QWidget *registrationWindow;
 //   static QWidget *levelWindow;
    //static QGraphicsView *mainView;
};

#endif // WINDOWMANAGER_H
