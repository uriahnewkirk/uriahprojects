#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <QDialog>
#include "mainwindow.h"
class MainWindow;

namespace Ui {
class instructions;
}

class instructions : public QDialog
{
    Q_OBJECT

public:
    explicit instructions(QWidget *parent = 0);
    ~instructions();

private slots:
    void on_mainM_clicked();

private:
    Ui::instructions *ui;
    MainWindow *mainW;
};

#endif // INSTRUCTIONS_H
