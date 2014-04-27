#include "taskthread.h"
#include "task.h"
#include "tabusearch.h"

#include <iostream>

using namespace std;

TaskThread::TaskThread(QObject *parent):
    QThread(parent)
{
    Taskparent = (Task*)parent;
    engine = new TabuSearch(this);
    m_bToSuspend = false;
}

void TaskThread::insert_data(std::unique_ptr<Result> p_result,int option)
{
    this->option = option;
    m_result = std::move(p_result);
}

void TaskThread::run()
{
    switch (option)
    {
        case 1:
            m_result = std::move(engine->generateFirstResult(std::move(m_result)));
        break;

        case 2:
            m_result = std::move(engine->optimized(std::move(m_result)));
        break;
    }
}

void TaskThread::suspend()
{
    m_bToSuspend = true;
}

void TaskThread::resume()
{
    if (!m_bToSuspend)
        return;

    m_bToSuspend = false;
    m_waitCondt.wakeOne();
}
