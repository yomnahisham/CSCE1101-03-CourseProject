#ifndef LEVEL_H
#define LEVEL_H

#include <QDialog>

namespace Ui {
class Level;
}

class Level : public QDialog
{
    Q_OBJECT

public:
    explicit Level(QWidget *parent = nullptr);
    ~Level();

private slots:
    void on_Level1_clicked();

private:
    Ui::Level *ui;
};

#endif // LEVEL_H
