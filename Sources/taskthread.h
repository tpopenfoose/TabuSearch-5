#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include "globalne.h"
#include "result.h"
#include <memory>

class Task;
class TabuSearch;
class TaskMainWindow;

class TaskThread : public QThread
{
public:
    TaskThread(QObject *parent = 0);
    void run();
    void insert_data(std::unique_ptr<Result> p_result, int option);
    int option;

    void suspend(void);
    void resume(void);

private:

    bool m_bToSuspend;

    QWaitCondition m_waitCondt;

    std::unique_ptr<Result> m_result;
    Task *Taskparent;
    TabuSearch *engine;

friend class TabuSearch;
friend class TaskMainWindow;
friend class Task;

};

#endif // TASKTHREAD_H
