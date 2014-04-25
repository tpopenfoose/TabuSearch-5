#include "sharedmemory.h"
#include "mainscreen.h"
#include "tasklayout.h"
#include "taskbuttongroup.h"
#include "taskbutton.h"
#include "task.h"

#include "iostream"
#include <QApplication>
#include <QDesktopWidget>

using namespace std;

SharedMemory::SharedMemory(){}

SharedMemory* SharedMemory::_instance = 0;

SharedMemory* SharedMemory::Instance()
{
    if(_instance == 0)
        _instance = new SharedMemory;

    return _instance;
}

void SharedMemory::initMainWindow(QMainWindow* parent)
{
    mainscreen = new MainScreen(parent);
    parent->setCentralWidget(mainscreen);
}

void SharedMemory::createMainScreen(QWidget* innerScreen)
{
    mainlayout = new TaskLayout(innerScreen);

    buttonGroup = new TaskButtonGroup();

    innerScreen->setLayout(mainlayout);
    innerScreen->setMaximumWidth(screensize.width()-19);

    TaskButton *button = new TaskButton();
    mainlayout->addWidget(button);
    buttonGroup->addButton(button);
}

bool SharedMemory::instanceExist(QAbstractButton* button)
{
    int position = buttonGroup->buttons().indexOf(button,0);

    return ((position+1) == buttonGroup->buttons().size()) ? false : true;
}

Task* SharedMemory::getTask(QAbstractButton* button)
{
    int position = buttonGroup->buttons().indexOf(button,0);

    return taskList[position];
}

bool SharedMemory::onlyOneButton(void)
{
    return (buttonGroup->buttons().size() == 1) ? true : false;
}

void SharedMemory::readScreenSize(void)
{
    screensize = QApplication::desktop()->availableGeometry();
}

QRect SharedMemory::getScreenSize(void)
{
    return screensize;
}

void SharedMemory::addInstance(void)
{
    TaskButton* button = new TaskButton();
    mainlayout->addWidget(button);
    buttonGroup->addButton(button);
    taskList.append( new Task() );
}

void SharedMemory::deleteInstance(Task* task)
{
    int pos = taskList.indexOf(task,0);

    QPushButton *button = (QPushButton*)(buttonGroup->buttons().at(pos));
    buttonGroup->removeButton(button);
    mainlayout->removeWidget(button);
    taskList.removeAt(pos);

    button->~QPushButton();
}
