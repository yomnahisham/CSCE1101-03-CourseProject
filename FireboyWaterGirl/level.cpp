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
    Manager.showWindow(WindowManager::main);
    hide();
}

