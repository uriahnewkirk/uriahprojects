#include "selectplayers.h"
#include "ui_selectplayers.h"
#include "mainwindow.h"
#include "board.h"

selectPlayers::selectPlayers(QWidget *parent) : QDialog(parent), ui(new Ui::selectPlayers)
{
    ui->setupUi(this);
    QPixmap pix("/home/uriahnewkirk/Desktop/water/comp410/project/atfour.jpg");
    //int w = ui->bgLabel->width();
    //int h = ui->bgLabel->height();
    //ui->bgLabel->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    //remove line edit text background to make it blend in better
    ui->title->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    ui->playersText->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    ui->timerText->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    ui->timerP1Text->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    ui->timerP2Text->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    ui->timerP3Text->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    ui->timerP4Text->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    ui->cSelectText->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    ui->box_totalP->setCurrentIndex(2);

    ui->tBox_P1->setCurrentIndex(8);
    ui->tBox_P2->setCurrentIndex(8);
    ui->tBox_P3->setCurrentIndex(8);
    ui->tBox_P4->setCurrentIndex(8);

    ui->boxP1->setCurrentIndex(0);
    ui->boxP2->setCurrentIndex(1);
    ui->boxP3->setCurrentIndex(2);
    ui->boxP4->setCurrentIndex(3);

//    connect(ui->box_totalP,SIGNAL(currentIndexChanged(int)),ui->boxP4,SLOT(setEnabled(false)));

}

selectPlayers::~selectPlayers()
{
    delete ui;
}

void selectPlayers::on_backB_clicked()
{
    hide();
    mainW = new MainWindow(this);
    mainW->show();
}



void selectPlayers::on_box_totalP_currentIndexChanged(int index)
{
    //check if same player selected multiple times
    if(index==0) {
        //remove/show appropriate checkboxes
        ui->boxP2->setVisible(true);
        ui->boxP3->setVisible(false);
        ui->boxP4->setVisible(false);


        ui->timerP2Text->setVisible(true);
        ui->timerP3Text->setVisible(false);
        ui->timerP4Text->setVisible(false);
        ui->labelP2->setVisible(true);
        ui->labelP3->setVisible(false);
        ui->labelP4->setVisible(false);
        ui->tBox_P2->setVisible(true);
        ui->tBox_P3->setVisible(false);
        ui->tBox_P4->setVisible(false);
    }
    else if(index==1) {
        //remove/show appropriate checkboxes
        ui->boxP2->setVisible(true);
        ui->boxP3->setVisible(true);
        ui->boxP4->setVisible(false);


        ui->timerP2Text->setVisible(true);
        ui->timerP3Text->setVisible(true);
        ui->timerP4Text->setVisible(false);
        ui->labelP2->setVisible(true);
        ui->labelP3->setVisible(true);
        ui->labelP4->setVisible(false);
        ui->tBox_P2->setVisible(true);
        ui->tBox_P3->setVisible(true);
        ui->tBox_P4->setVisible(false);

    }
    else if(index==2){
        //remove/show appropriate checkboxes
        ui->boxP2->setVisible(true);
        ui->boxP3->setVisible(true);
        ui->boxP4->setVisible(true);



        ui->timerP2Text->setVisible(true);
        ui->timerP3Text->setVisible(true);
        ui->timerP4Text->setVisible(true);
        ui->labelP2->setVisible(true);
        ui->labelP3->setVisible(true);
        ui->labelP4->setVisible(true);
        ui->tBox_P2->setVisible(true);
        ui->tBox_P3->setVisible(true);
        ui->tBox_P4->setVisible(true);


    }
}


void selectPlayers::on_nextB_clicked()
{
    hide();
    the_board = new board(this);
    the_board->show();

    board::playerC = ui->box_totalP->currentIndex() +2;

    board::p1Time = ui->tBox_P1->currentIndex() +2;
    board::p2Time = ui->tBox_P2->currentIndex() +2;
    board::p3Time = ui->tBox_P3->currentIndex() +2;
    board::p4Time = ui->tBox_P4->currentIndex() +2;


    board::p1Name = ui->boxP1->currentText();
    board::p2Name = ui->boxP2->currentText();
    board::p3Name = ui->boxP3->currentText();
    board::p4Name = ui->boxP4->currentText();


}
