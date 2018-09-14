#include "congratulations.h"
#include "ui_congratulations.h"
#include "board.h"
#include "mainwindow.h"
class MainWindow;

int the_winner;

congratulations::congratulations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::congratulations)
{
    ui->setupUi(this);

    the_winner = board::winP;

    if(the_winner==1) {
        ui->winner_the->setPlainText("Congratulations, Player 1 is the winner!");
    }
    else if(the_winner==2) {
        ui->winner_the->setPlainText("Congratulations, Player 2 is the winner!");
    }
    else if(the_winner==3) {
        ui->winner_the->setPlainText("Congratulations, Player 3 is the winner!");
    }
    else {
        ui->winner_the->setPlainText("Congratulations, Player 4 is the winner!");
    }

}

congratulations::~congratulations()
{
    delete ui;
}

void congratulations::on_returnM_clicked()
{
    hide();
    mainW2 = new MainWindow(this);
    mainW2->show();
}

void congratulations::on_quitG_clicked()
{
    close();
}
