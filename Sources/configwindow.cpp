#include "configwindow.h"
#include "sharedmemory.h"
#include "configtabone.h"
#include "configtabtwo.h"
#include "configtabthree.h"
#include "configtabfour.h"
#include <iostream>

using namespace std;

extern SharedMemory memory;

ConfigWindow::ConfigWindow(QWidget *parent) :
    QFrame(parent)
{
    createMainLayout();

    createConnections();

    setFixedSize(350,400);
}

void ConfigWindow::createMainLayout(void)
{
    createMainUI();

    tabs[0] = new ConfigTabOne(this);
    tabs[1] = new ConfigTabTwo(this);
    tabs[2] = new ConfigTabThree(this);
    tabs[3] = new ConfigTabFour(this);

    layouts = new QStackedLayout;

    for(int i = 0; i < tabsCount; i++)
        layouts->addWidget(tabs[i]);

    mainlayout = new QGridLayout;
    mainlayout->addWidget(tabBar,1,1,1-1);
    mainlayout->addLayout(layouts,2,1,1,-1);
    mainlayout->addWidget(cancelButton,3,1);
    mainlayout->addWidget(okButton,3,2);

    setLayout(mainlayout);
}

void ConfigWindow::createMainUI(void)
{
    tabBar = new QTabBar;
    tabBar->addTab("Dane");
    tabBar->addTab("Algorytm");
    tabBar->addTab("Lista Tabu");
    tabBar->addTab("Figury");
    tabBar->setFixedSize(250,25);

    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setFixedSize(60,30);
    okButton = new QPushButton(tr("OK"));
    okButton->setFixedSize(60,30);
}

void ConfigWindow::createConnections(void)
{
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancelAction()));
    connect(okButton,SIGNAL(clicked()),this,SLOT(okAction()));
    connect(tabBar,SIGNAL(currentChanged(int)),this,SLOT(tabChange(int)));
}

void ConfigWindow::tabChange(int screenNumber)
{
    layouts->setCurrentWidget(tabs[screenNumber]);
}

void ConfigWindow::cancelAction(void)
{
    for(int i = 0; i < tabsCount; i++)
        tabs[i]->cancelChanges();

    this->hide();
}

void ConfigWindow::okAction(void)
{
    for(int i = 0; i < tabsCount; i++)
        tabs[i]->updateChanges();

    this->hide();
}

ConfigData ConfigWindow::getConfigData(void)
{
    ConfigData data;

    for(int i = 0; i < tabsCount; i++)
       data =  tabs[i]->getConfigData(data);

    return data;
}

void ConfigWindow::loadConfig(ConfigData data)
{
    for(int i = 0; i < tabsCount; i++)
       tabs[i]->loadConfigData(data);
}

