#ifndef TASKTHREAD_H
#define TASKTHREAD_H

#include <QWaitCondition>
#include "result.h"
#include <memory>

class TabuSearch;

class TaskThread : public QObject
{
    Q_OBJECT
public:
    TaskThread();

    void start_thread(std::shared_ptr<Result> p_result, const ConfigData &p_data, int p_option);

    void suspend(void);
    void resume(void);
    TabuSearch *engine;

    std::shared_ptr<Result> get_result();

signals:

    void finished(int p_option);

private:
    void run_in_thread();
    bool m_bToSuspend;
    int m_option;
    QWaitCondition m_waitCondt;

    std::shared_ptr<Result> m_result;
    ConfigData m_data;


friend class TabuSearch;
};

#endif // TASKTHREAD_H
