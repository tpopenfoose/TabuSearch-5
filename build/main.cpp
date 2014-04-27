#include "mainwindow.h"
#include <iostream>
#include <QApplication>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(files);
    MainWindow mainwindow;

    mainwindow.show();

    return app.exec();
}
