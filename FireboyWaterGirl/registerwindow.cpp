#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "allusers.h""

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui-> passerror -> hide();
    ui-> usererror -> hide();

}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_regButton_clicked()
{   //check for same username
    bool uniqueUser = false;
    QString username;
    /*for ()
    {
        if (!search(ui->userline -> text()))
        {
            uniqueUser = true;
        }
    }


    //check password and repeat is the same
    QString password;
    bool pass = false;
    if (ui-> passline -> text() == ui-> repeatline -> text())
    {
        password = ui-> passline -> text();
        pass = true;
    }
    else
    {
        ui -> passerror -> show();
    }
    //add user to allusers database
   // if(uniqueUser && pass)
        //newUser(username, password)
*/
}

