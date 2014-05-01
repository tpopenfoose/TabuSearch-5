#include "mainscreen.h"
#include "tasklayout.h"
#include "sharedmemory.h"
#include "taskbuttongroup.h"
#include "taskbutton.h"

MainScreen::MainScreen(QWidget *parent):
    QScrollArea(parent)
{
    setWidgetResizable(true);

    innerScreen = new QWidget(this);

    SharedMemory::Instance()->createMainScreen(innerScreen);

    setWidget(innerScreen);
}





