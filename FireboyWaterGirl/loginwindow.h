#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "user.h"
#include <QDialog>
#include <QtSQL>
#include <QtCore>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginPush_clicked();
    void on_registerPush_clicked();

private:
    Ui::LoginWindow *ui;
    User* loggedUser;
};

#endif // LOGINWINDOW_H
