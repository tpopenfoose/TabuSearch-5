#include "configtabthree.h"
#include "defaultconfig.h"

ConfigTabThree::ConfigTabThree(QWidget *parent) :
    ConfigTab(parent)
{
    tabuListSize = g_tabu_list_size;
    tabuListTime = g_tabu_list_time;

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
    tabuListSizeLabel = new QLabel(g_tabu_list_size_name.c_str());
    tabuListTimeLabel = new QLabel(g_tabu_list_time_name.c_str());

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
    this->tabuListSize = data.tabusize;
    this->tabuListTime = data.tabutime;

    cancelChanges();
}
