#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "instructions.h"
#include "selectplayers.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/home/uriahnewkirk/Desktop/water/comp410/project/statue1.jpg");
    int w = ui->labelM->width();
    int h = ui->labelM->height();
    ui->labelM->setPixmap(pix.scaled(w, h, Qt::IgnoreAspectRatio, Qt::FastTransformation));
//    ui->title_game->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startG_clicked()
{
    hide();
    selectP = new selectPlayers(this);
    selectP->show();
}

void MainWindow::on_viewI_clicked()
{
    hide();
    instructW = new instructions(this);
    instructW->show();
}



void MainWindow::on_exitG_clicked()
{
    close();
}
