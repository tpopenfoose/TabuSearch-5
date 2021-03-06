#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include "globalne.h"

class Task;
class TabuSearch;
class TaskMainWindow;

class TaskThread : public QThread
{
public:
    TaskThread(QObject *parent = 0);
    void run();
    void insert_data(TSF tsf, int option);
    int option;

    void suspend(void);
    void resume(void);

private:

    bool m_bToSuspend;

    QWaitCondition m_waitCondt;

    TSF tsf;
    Task *Taskparent;
    TabuSearch *engine;
    QVector<Figure> result;

    //QVector< QVector<Figure> > TSB;

friend class TabuSearch;
friend class TaskMainWindow;
friend class Task;

};

#endif // TASKTHREAD_H
