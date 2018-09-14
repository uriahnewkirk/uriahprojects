#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "instructions.h"
#include "selectplayers.h"
#include "board.h"
#include "congratulations.h"
class instructions;
class selectPlayers;
class board;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startG_clicked();

    void on_viewI_clicked();

    void on_exitG_clicked();

private:
    Ui::MainWindow *ui;
    instructions *instructW;
    selectPlayers *selectP;
    //board *the_board;
};

#endif // MAINWINDOW_H
