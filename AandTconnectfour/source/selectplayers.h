#ifndef SELECTPLAYERS_H
#define SELECTPLAYERS_H

#include <QDialog>
#include "mainwindow.h"
#include "board.h"
class MainWindow;
class board;

namespace Ui {
class selectPlayers;
}

class selectPlayers : public QDialog
{
    Q_OBJECT

public:
    explicit selectPlayers(QWidget *parent = 0);
    ~selectPlayers();

private slots:
    void on_backB_clicked();

    void on_box_totalP_currentIndexChanged(int index);

    void on_nextB_clicked();

private:
    Ui::selectPlayers *ui;
    MainWindow *mainW;
    board *the_board;
};

#endif // SELECTPLAYERS_H
