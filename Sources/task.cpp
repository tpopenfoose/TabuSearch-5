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
}

void Task::show_window(void)
{
    mainwindow->show();
}

Task::~Task()
{

}

