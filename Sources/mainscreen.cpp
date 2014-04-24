#include "mainscreen.h"
#include "tasklayout.h"
#include "sharedmemory.h"
#include "taskbuttongroup.h"
#include "taskbutton.h"

#include <iostream>
using namespace std;

//extern SharedMemory memory;

MainScreen::MainScreen(QWidget *parent):
    QScrollArea(parent)
{
    setWidgetResizable(true);

    innerScreen = new QWidget(this);

    //memory.createMainScreen(innerScreen);
    SharedMemory::Instance()->createMainScreen(innerScreen);

    setWidget(innerScreen);
}





