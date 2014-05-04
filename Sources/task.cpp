#include "task.h"
#include "sharedmemory.h"
#include "tabusearch.h"
#include <iostream>

extern SharedMemory memory;

Task::Task(QObject *parent) :
    QObject(parent)
{
    m_result = std::unique_ptr<Result>(new Result);

    config = new ConfigWindow();
    taskthread = new TaskThread();
    mainwindow = new TaskMainWindow();
    mainwindow->show();

    connect(taskthread->engine,SIGNAL(stats(int,int,int)),mainwindow,SLOT(update_progress(int,int,int)));
    connect(mainwindow,SIGNAL(random_button_clicked()),this,SLOT(random_Action()));
    connect(mainwindow,SIGNAL(start_button_clicked()),this,SLOT(start_Action()));
    connect(mainwindow,SIGNAL(pause_button_clicked(bool)),this,SLOT(pause_Action(bool)));
    connect(mainwindow,SIGNAL(config_button_clicked()),this,SLOT(config_Action()));
    connect(mainwindow,SIGNAL(exit_button_clicked()),this,SLOT(exit_action()));
    connect(mainwindow,SIGNAL(delete_task()),this,SLOT(delete_task()));
    connect(this,SIGNAL(finished(int)),mainwindow,SLOT(thread_finished(int)));
    connect(taskthread,SIGNAL(finished(int)),this,SLOT(thread_finished(int)));
    connect(this,SIGNAL(exit(bool)),mainwindow,SLOT(process_exit(bool)));
}

void Task::random_Action()
{
    m_result->set_data(config->getConfigData());
    taskthread->start_thread(std::move(m_result), 1);
}

void Task::start_Action()
{
    m_result->set_data(config->getConfigData());
    taskthread->start_thread(std::move(m_result), 2);
}

void Task::thread_finished(int p_action)
{
    m_result = std::move(taskthread->get_result());
    switch (p_action)
    {
        case 1:
            mainwindow->display_result(*m_result,1);
        break;

        case 2:
            mainwindow->display_result(*m_result,2);
        break;
    }

    emit finished(p_action);
}

void Task::pause_Action(bool toggle)
{
    if(toggle)
        taskthread->suspend();
    else
        taskthread->resume();
}

void Task::config_Action()
{
    config->show();
}

void Task::exit_action()
{
    emit exit(SharedMemory::Instance()->onlyOneButton());
}

void Task::delete_task()
{
    SharedMemory::Instance()->deleteInstance(this);
}

void Task::show_window(void)
{
    mainwindow->show();
}

Task::~Task()
{

}

