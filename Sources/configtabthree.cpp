#include "configtabthree.h"
#include <iostream>

using namespace std;

ConfigTabThree::ConfigTabThree(QWidget *parent) :
    ConfigTab(parent)
{
    tabuListSize = 20;
    tabuListTime = 10;

    createLayout();
}

void ConfigTabThree::createLayout(void)
{
    createUI();

    layout = new QGridLayout(this);
    layout->addWidget(tabuListSizeLabel,1,1);
    layout->addWidget(tabuListSizeLineEdit,1,2);

    layout->addWidget(tabuListTimeLabel,2,1);
    layout->addWidget(tabuListTimeLineEdit,2,2);

    setLayout(layout);
}

void ConfigTabThree::createUI(void)
{
    tabuListSizeLabel = new QLabel(tr("Długość listy Tabu"));
    tabuListTimeLabel = new QLabel(tr("Czas pobytu na Liście Tabu"));

    tabuListSizeLineEdit = new QLineEdit(QString::number(tabuListSize,10));
    tabuListSizeLineEdit->setFixedSize(60,25);

    tabuListTimeLineEdit = new QLineEdit(QString::number(tabuListTime,10));
    tabuListTimeLineEdit->setFixedSize(60,25);
}

void ConfigTabThree::cancelChanges(void)
{
    tabuListSizeLineEdit->setText(QString::number(tabuListSize,10));
    tabuListTimeLineEdit->setText(QString::number(tabuListTime,10));
}

void ConfigTabThree::updateChanges(void)
{
    tabuListSize = tabuListSizeLineEdit->text().toInt();
    tabuListTime = tabuListTimeLineEdit->text().toInt();
}

ConfigData ConfigTabThree::getConfigData(ConfigData data)
{
    data.tabusize = this->tabuListSize;
    data.tabutime = this->tabuListTime;

    return data;
}

void ConfigTabThree::loadConfigData(ConfigData data)
{
    //cout<<data.tabusize<<endl;
    //cout<<data.tabutime<<endl;

    this->tabuListSize = data.tabusize;
    this->tabuListTime = data.tabutime;

    cancelChanges();
}
