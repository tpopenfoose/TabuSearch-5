#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <mainscreen.h>
#include <memory>

class MainWindow : public QMainWindow
{
    public:

        MainWindow(QWidget *parent = 0);

    private:

        QMenu *mainMenu;
        QMenu *helpMenu;
        QAction *quitAction;
        std::unique_ptr<MainScreen> m_mainscreen;

        void create_connections(void);
        void create_menuBar(void);
        void create_actions(void);

    protected:
        void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
