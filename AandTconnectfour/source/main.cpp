#include "mainwindow.h"
#include <QApplication>
#include <iostream>

//void placeToken(int j) {
//    if(j>2) {
//        std::cout << "fire" << std::endl;
//    }

//}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
