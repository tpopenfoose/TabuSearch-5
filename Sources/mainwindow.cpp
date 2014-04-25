#include "mainwindow.h"
#include "sharedmemory.h"
#include "files.h"

#include <iostream>
using namespace std;
#include <QAction>
#include <QMenu>
#include <QMenuBar>

//extern SharedMemory memory;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    SharedMemory::Instance()->readScreenSize();
    SharedMemory::Instance()->initMainWindow(this);
    //memory.readScreenSize();
    //memory.initMainWindow(this);

    create_actions();

    create_menuBar();

    create_connections();

    showMaximized();
    setWindowIcon( QIcon(logo_png.c_str()));
}

void MainWindow::create_actions(void)
{
    quitAction = new QAction("Exit", this);
    quitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
}

void MainWindow::create_menuBar(void)
{
    mainMenu = new QMenu("Menu", this);
    menuBar()->addMenu(mainMenu);

    mainMenu->addSeparator();
    mainMenu->addAction(quitAction);

    helpMenu = new QMenu("Help", this);
    menuBar()->addMenu(helpMenu);

    helpMenu->addAction("About", qApp, SLOT(aboutQt()));
    menuBar()->setFixedHeight(21);
}

void MainWindow::create_connections(void)
{
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::closeEvent( QCloseEvent * event)
{
    //qApp->
   // qApp->closeAllWindows();
    qApp->quit();
}

