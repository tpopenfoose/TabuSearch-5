#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>

//class TaskButton;
//class TaskButtonGroup;
//class Task;
//class MainScreen;


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        MainWindow(QWidget *parent = 0);

    private:

        QMenu *mainMenu;
        QMenu *helpMenu;
        QAction *quitAction;

        void create_connections(void);
        void create_menuBar(void);
        void create_actions(void);

    protected:
        void closeEvent( QCloseEvent * event);

    signals:

       void start_TabuSearch(void);
       void set_screen(int num);
       void send(QString);
};

#endif // MAINWINDOW_H
