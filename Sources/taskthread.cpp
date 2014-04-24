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

void TaskThread::insert_data(TSF tsf,int option)
{
    this->option = option;
    this->tsf = tsf;
}

void TaskThread::run()
{
    switch (option)
    {
        case 1:
            engine->generateFirstResult(tsf.data);
        break;

        case 2:
            engine->begin(tsf);
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
