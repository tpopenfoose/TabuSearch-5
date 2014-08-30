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

void TaskThread::start_thread(std::shared_ptr<Result> p_result, const ConfigData& p_data, int p_option)
{
    m_option = p_option;
    m_result = p_result;
    m_data = p_data;
    std::thread worker_thread(&TaskThread::run_in_thread, this);
    worker_thread.detach();
}

void TaskThread::run_in_thread()
{
    switch (m_option)
    {
        case 1:
            m_result = engine->generateFirstResult(m_result, m_data);
        break;

        case 2:
            m_result = engine->optimized(m_result);
        break;
    }

    emit finished(m_option);
}

std::shared_ptr<Result> TaskThread::get_result()
{
    return m_result;
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
