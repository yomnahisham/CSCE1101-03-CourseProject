#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include "user.h"
#include "allusers.h"
#include <QDialog>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_regButton_clicked();

    void on_backButton_clicked();

private:
    Ui::RegisterWindow *ui;
    User* user;
    AllUsers* users;
};

#endif // REGISTERWINDOW_H
