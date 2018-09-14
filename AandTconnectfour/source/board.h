#ifndef BOARD_H
#define BOARD_H

#include <QDialog>
#include "congratulations.h"
#include "selectplayers.h"
#include "mainwindow.h"
#include <QString>
class MainWindow;
class congratulations;
class selectPlayers;

namespace Ui {
class board;
}

class board : public QDialog
{
    Q_OBJECT

public:
    explicit board(QWidget *parent = 0);
    ~board();
    static int p1Time, p2Time, p3Time, p4Time, playerC, playerturn, turnCount, winP;
    static QString p1Name, p2Name, p3Name, p4Name;
    static QString four_the[4];
    static bool p1T, p2T, p3T, p4T;
    static bool p1Status, p2Status, p3Status, p4Status;
    void showBoard();
    bool winner();
    bool boardFull();
    void startGame();
    void switchTurn();
    void endGame();


private slots:
    void on_mMenu_clicked();

    void on_placeToken_clicked();

private:
    Ui::board *ui;
    MainWindow *mainW;
    congratulations *done;

};

#endif // BOARD_H
