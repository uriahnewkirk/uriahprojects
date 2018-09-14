#include "instructions.h"
#include "ui_instructions.h"
#include "mainwindow.h"

instructions::instructions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instructions)
{
    ui->setupUi(this);

    ui->title_the->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
}

instructions::~instructions()
{
    delete ui;
}

void instructions::on_mainM_clicked()
{
    hide();
    mainW = new MainWindow(this);
    mainW->show();


}
