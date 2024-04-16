#include "windowmanager.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "level.h"

QWidget* WindowManager::loginWindow = nullptr;
QWidget* WindowManager::registrationWindow = nullptr;
QWidget* WindowManager::levelWindow = nullptr;
QGraphicsView* WindowManager::mainView = nullptr;

void WindowManager::showLoginWindow() {
    loginWindow->show();
    if (registrationWindow)
        registrationWindow->hide();
    if (levelWindow)
        levelWindow->hide();
    if (mainView)
        mainView->hide();
}

void WindowManager::showRegistrationWindow() {
    if (loginWindow)
        loginWindow->hide();
    registrationWindow->show();
    if (levelWindow)
        levelWindow->hide();
    if (mainView)
        mainView->hide();
}

void WindowManager::showLevelWindow() {
    if (loginWindow)
        loginWindow->hide();
    if (registrationWindow)
        registrationWindow->hide();
    levelWindow->show();
    if (mainView)
        mainView->hide();
}

void WindowManager::showMainView() {
    if (loginWindow)
        loginWindow->hide();
    if (registrationWindow)
        registrationWindow->hide();
    if (levelWindow)
        levelWindow->hide();
    mainView->show();
}
