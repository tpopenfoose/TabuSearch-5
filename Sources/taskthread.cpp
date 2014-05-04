#include "taskthread.h"
#include "task.h"
#include "tabusearch.h"

#include <thread>
#include <iostream>

using namespace std;

TaskThread::TaskThread()
{
    engine = new TabuSearch(this);
    m_bToSuspend = false;
}

void TaskThread::start_thread(std::unique_ptr<Result> p_result,int p_option)
{
    m_option = p_option;
    m_result = std::move(p_result);
    std::thread worker_thread(&TaskThread::run_in_thread, this);
    worker_thread.detach();
}

void TaskThread::run_in_thread()
{
    switch (m_option)
    {
        case 1:
            m_result = std::move(engine->generateFirstResult(std::move(m_result)));
        break;

        case 2:
            m_result = std::move(engine->optimized(std::move(m_result)));
        break;
    }

    emit finished(m_option);
}

std::unique_ptr<Result> TaskThread::get_result()
{
    return std::move(m_result);
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
