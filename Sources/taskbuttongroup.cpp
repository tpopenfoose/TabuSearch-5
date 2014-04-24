#include "taskbuttongroup.h"
#include "taskbutton.h"
#include "tasklayout.h"
#include "sharedmemory.h"
#include "task.h"
#include "files.h"

#include <iostream>
using namespace std;

//extern SharedMemory memory;

TaskButtonGroup::TaskButtonGroup(QWidget *parent) :
    QButtonGroup(parent)
{
    connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));
}

void TaskButtonGroup::buttonClick(QAbstractButton* button)
{
    //if(memory.instanceExist(button))
    if(SharedMemory::Instance()->instanceExist(button))
    {
        //memory.getTask(button)->show_window();
        SharedMemory::Instance()->getTask(button)->show_window();
    }

    else
    {
        button->setIcon(QIcon(calculate_png.c_str()));
        //memory.addInstance();
        SharedMemory::Instance()->addInstance();
    }
}
