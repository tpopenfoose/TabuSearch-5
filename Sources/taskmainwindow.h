#ifndef TASKMAINWINDOW_H
#define TASKMAINWINDOW_H

#include "globalne.h"
#include "result.h"
#include <QToolBar>
#include <QLCDNumber>
#include <QProgressBar>
#include <QLabel>
#include <QMainWindow>

class Task;

class TaskMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit TaskMainWindow(QObject *parent);
    
signals:
    
public slots:

    void update_progress(int value,int all,int time);

private slots:

    void save_Action(void);
    void load_Action(void);

    void config_Action(void);
    void random_Action(void);
    void start_Action(void);
    void pause_Action(bool toggle);

    void dataBase_Action(void);
    void clear_Action(void);

    void maximize_Action(bool toggle);
    void exit_Action(void);

    void thread_finished(void);    

private:

    QToolBar *toolbar;

    QAction *saveAction;
    QAction *loadAction;

    QAction *configAction;
    QAction *randomAction;
    QAction *startAction;
    QAction *pauseAction;

    QAction *databaseAction;
    QAction *clearAction;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *exitAction;

    QLCDNumber *lcd1;
    QLCDNumber *lcd2;
    QLCDNumber *lcd3;
    QLCDNumber *lcd4;
    QProgressBar *progressbar;
    QLabel *ETL;

    QLabel *resultlabel1;
    QLabel *resultlabel2;
    QLabel *resultlabel3;
    QLabel *resultlabel4;
    QLabel *resultlabel5;
    QLabel *resultlabel6;

    bool save;

    Task* Taskparent;
    std::unique_ptr<Result> m_result;
    std::vector<std::shared_ptr<Shape>> result;


    void delete_task(void);
    void renumerate(void);

    void createActions(void);
    void createToolBar(void);
    void createConnections(void);
    void createStatusBox(void);
    void createProgresBox(void);
    void createScrollArea(void);
    void createDockBoxes(void);
    void save_data(void);
    void read_data(void );

    int waste(std::vector<std::shared_ptr<Shape>> v);

friend class Task;

};

#endif // TASKMAINWINDOW_H
