#include "configtabtwo.h"

ConfigTabTwo::ConfigTabTwo(QWidget *parent) :
    ConfigTab(parent)
{
    iterationCount = 50;
    changeCount = 5;

    createLayout();

    connect(chargePercentageSlider,SIGNAL(valueChanged(int)),this,SLOT(sliderChange(int)));
}

void ConfigTabTwo::createLayout(void)
{
    createUI();

    layout = new QGridLayout(this);

    layout->addWidget(iterationLabel,1,1);

    layout->addWidget(iterationLineEdit,1,2);

    layout->addWidget(chargePercentageLabel,2,1);
    layout->addWidget(chargePercentageSlider,2,2);

    setLayout(layout);
}

void ConfigTabTwo::createUI(void)
{
    iterationLabel = new QLabel(tr("Ilość iteracji"));

    iterationLineEdit = new QLineEdit(QString::number(iterationCount,10));
    iterationLineEdit->setFixedSize(60,25);

    chargePercentageSlider = new QSlider(Qt::Horizontal);
    chargePercentageSlider->setFixedSize(100,25);
    chargePercentageSlider->setRange(5,100);
    chargePercentageSlider->setSingleStep(1);
    chargePercentageSlider->setValue(changeCount);

    chargePercentageLabel = new QLabel(tr("Wiekość sąsiedztwa: ")+QString::number(chargePercentageSlider->value(),10)+"%");
    chargePercentageLabel->setFixedSize(150,30);
}

void ConfigTabTwo::sliderChange(int changeCount)
{
    chargePercentageLabel->setText(tr("Wielkość sąsiedztwa: ")+QString::number(changeCount,10)+"%");
}

void ConfigTabTwo::cancelChanges(void)
{
    chargePercentageSlider->setValue(changeCount);
    iterationLineEdit->setText(QString::number(iterationCount,10));
}

void ConfigTabTwo::updateChanges(void)
{
    changeCount = chargePercentageSlider->value();
    iterationCount = iterationLineEdit->text().toInt();
}

ConfigData ConfigTabTwo::getConfigData(ConfigData data)
{
    data.procent = this->changeCount;
    data.iteration = this->iterationCount;

    return data;
}

void ConfigTabTwo::loadConfigData(ConfigData data)
{
    this->changeCount = data.procent;
    this->iterationCount = data.iteration;

    cancelChanges();
}
