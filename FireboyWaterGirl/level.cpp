#include "level.h"
#include "ui_level.h"

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

}

