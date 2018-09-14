#ifndef CONGRATULATIONS_H
#define CONGRATULATIONS_H

#include <QDialog>
#include "mainwindow.h"
#include "board.h"
class MainWindow;
class board;

namespace Ui {
class congratulations;
}

class congratulations : public QDialog
{
    Q_OBJECT

public:
    explicit congratulations(QWidget *parent = 0);
    ~congratulations();

private slots:
    void on_returnM_clicked();

    void on_quitG_clicked();

private:
    Ui::congratulations *ui;
    MainWindow *mainW2;
};

#endif // CONGRATULATIONS_H
