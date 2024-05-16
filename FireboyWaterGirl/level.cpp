#include "level.h"
#include "ui_level.h"
#include "windowmanager.h"

Level::Level(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Level)
{
    ui->setupUi(this);
}

Level::~Level()
{
    delete ui;
}

void Level::on_Level1_clicked()
{
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 1);
    hide();
}


void Level::on_level2B_clicked()
{
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 2);
    hide();
}


void Level::on_level3B_clicked()
{
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 3);
    hide();
}


void Level::on_level4B_clicked()
{
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 4);
    hide();
}


void Level::on_level5B_clicked()
{
    WindowManager Manager;
    Manager.showWindow(WindowManager::main, 5);
    hide();
}

