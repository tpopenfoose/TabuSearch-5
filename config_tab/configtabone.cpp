#include "configtabone.h"
#include "defaultconfig.h"

ConfigTabOne::ConfigTabOne(QWidget *parent) :
    ConfigTab(parent)
{
    width = g_width;
    height = g_height;
    size = g_size;

    createLayout();
}

void ConfigTabOne::createLayout(void)
{
    createUI();

    layout = new QGridLayout(this);

    layout->addWidget(widthLabel,1,1);
    layout->addWidget(widthLineEdit,1,2);

    layout->addWidget(heightLabel,2,1);
    layout->addWidget(heightLineEdit,2,2);

    layout->addWidget(sizeLabel,3,1);
    layout->addWidget(sizeLineEdit,3,2);

    setLayout(layout);
}

void ConfigTabOne::createUI(void)
{
    widthLabel = new QLabel(g_width_name.c_str());
    heightLabel = new QLabel(g_height_name.c_str());
    sizeLabel = new QLabel(g_size_name.c_str());

    widthLineEdit = new QLineEdit(QString::number(width,10));
    widthLineEdit->setFixedSize(60,25);

    heightLineEdit = new QLineEdit(QString::number(height,10));
    heightLineEdit->setFixedSize(60,25);

    sizeLineEdit = new QLineEdit(QString::number(size,10));
    sizeLineEdit->setFixedSize(60,25);
}

void ConfigTabOne::cancelChanges(void)
{
    widthLineEdit->setText(QString::number(width,10));
    heightLineEdit->setText(QString::number(height,10));
    sizeLineEdit->setText(QString::number(size,10));
}

void ConfigTabOne::updateChanges(void)
{
    width = widthLineEdit->text().toInt();
    height = heightLineEdit->text().toInt();
    size = sizeLineEdit->text().toInt();
}

ConfigData ConfigTabOne::getConfigData(ConfigData data)
{
    data.width = this->width;
    data.height = this->height;
    data.size = this->size;

    return data;
}

void ConfigTabOne::loadConfigData(ConfigData data)
{
    this->width = data.width;
    this->height = data.height;
    this->size = data.size;

    cancelChanges();
}
