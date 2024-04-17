#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

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
};

#endif // LOGINWINDOW_H
