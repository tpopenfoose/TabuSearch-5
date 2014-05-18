#include "mainwindow.h"
#include "files.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_mainscreen.reset(new MainScreen(this));
    setCentralWidget(m_mainscreen.get());

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

void MainWindow::closeEvent( QCloseEvent *)
{
    qApp->quit();
}

