#include "task.h"
#include "board.h"
#include "configwindow.h"
#include "taskmainwindow.h"
#include "sharedmemory.h"
#include "taskthread.h"
#include "tabusearch.h"
#include <iostream>

using namespace std;

extern SharedMemory memory;

Task::Task(QObject *parent) :
    QObject(parent)
{
    board1 = new Board();
    board2 = new Board();

    config = new ConfigWindow();
    taskthread = new TaskThread();
    mainwindow = new TaskMainWindow(this);
    mainwindow->show();

    connect(taskthread->engine,SIGNAL(stats(int,int,int)),mainwindow,SLOT(update_progress(int,int,int)));
    //connect(mainwindow->randomAction,SIGNAL(triggered()),this,SLOT(random_Action()));
}

void Task::random_Action()
{
    //cout<<"random_test1"<<endl;
    //m_result->set_data(Taskparent->config->getConfigData());
    //cout<<"random_test2"<<endl;
    //Taskparent->taskthread->insert_data(std::move(m_result),1);
    //Taskparent->taskthread->start();
}

void Task::show_window(void)
{
    mainwindow->show();
}

Task::~Task()
{

}

