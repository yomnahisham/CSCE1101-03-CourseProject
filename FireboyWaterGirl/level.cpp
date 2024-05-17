#include "level.h"
#include "ui_level.h"
#include "windowmanager.h"

Level::Level(QWidget *parent, User* loggeduser)
    : QDialog(parent)
    , ui(new Ui::Level)
{
    ui->setupUi(this);
    user = loggeduser;
}

Level::~Level()
{
    delete ui;
}

void Level::on_Level1_clicked()
{
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 1, user);
    hide();
}


void Level::on_level2B_clicked()
{
    // starts layout, 2
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 2, user);
    hide();
}


void Level::on_level3B_clicked()
{
    // starts layout, 3
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 3, user);
    hide();
}


void Level::on_level4B_clicked()
{
    // starts layout, 4
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 4, user);
    hide();
}


void Level::on_level5B_clicked()
{
    // starts layout, 5
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 5, user);
    hide();
}

