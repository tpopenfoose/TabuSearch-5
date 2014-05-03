#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include <QWaitCondition>
#include "globalne.h"
#include "result.h"
#include <memory>

class TabuSearch;

class TaskThread
{
public:
    TaskThread();

    std::unique_ptr<Result> start_thread(std::unique_ptr<Result> p_result, int p_option);

    void suspend(void);
    void resume(void);
    TabuSearch *engine;

private:
    void run_in_thread();
    bool m_bToSuspend;
    int m_option;
    QWaitCondition m_waitCondt;

    std::unique_ptr<Result> m_result;


friend class TabuSearch;
};

#endif // TASKTHREAD_H
