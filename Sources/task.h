#ifndef TASK_H
#define TASK_H

#include <QtGui>
#include "globalne.h"

class Board;
class ConfigWindow;
class TabuSearch;
class Inserter;
class TaskMainWindow;
class TaskThread;

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);

    void show_window(void);

    virtual ~Task();

private:

    QFile *file;

    //QVector<Center> first;

    Board *board1;
    Board *board2;
    ConfigWindow *config;

    TaskMainWindow *mainwindow;
    TaskThread *taskthread;


friend class TaskMainWindow;
friend class TabuSearch;

private slots:
    void random_Action();
    
signals:
    
public slots:
    
};

#endif // TASK_H
