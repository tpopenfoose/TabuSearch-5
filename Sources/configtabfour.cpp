#include "configtabfour.h"

CheckBoxGroup::CheckBoxGroup(QWidget *parent) :
    QButtonGroup(parent)
{
    setExclusive(false);
    connect(this, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(buttonClick(QAbstractButton*)));
}

void CheckBoxGroup::buttonClick(QAbstractButton* button)
{
    int checkBoxNumber = buttons().indexOf(button,0);
    bool isChecked = ((QCheckBox*)button)->isChecked();
    emit checkBoxClicked(checkBoxNumber,isChecked);
}

ShareSlider::ShareSlider(QWidget *parent) :
    QSlider(Qt::Horizontal,parent)
{
    setFixedSize(100,25);
    setRange(1,100);
    setSingleStep(1);
    setValue(100);
}

ConfigTabFour::ConfigTabFour(QWidget *parent) :
    ConfigTab(parent)
{
    for(int i = 0; i < figureCount; i++)
    {
        figures[i].checked = true;
        figures[i].procent = 100;
    }

    createLayout();

    for(int i = 0; i < figureCount; i++)
        connect(shareSlider[i],SIGNAL(valueChanged(int)),shareLabel[i],SLOT(setNum(int)));

    connect(checkBoxGroup, SIGNAL(checkBoxClicked(int,bool)), this, SLOT(checkBoxChange(int,bool)));
}

void ConfigTabFour::createLayout(void)
{
    checkBoxGroup = new CheckBoxGroup();

    createUI();

    layout = new QGridLayout(this);
    layout->addWidget(percentageShareLabel,1,2,1,2);

    layout->addWidget(shareCheckBox[0],2,1);
    layout->addWidget(shareCheckBox[1],3,1);
    layout->addWidget(shareCheckBox[2],4,1);
    layout->addWidget(shareCheckBox[3],5,1);

    layout->addWidget(shareLabel[0],2,2);
    layout->addWidget(shareLabel[1],3,2);
    layout->addWidget(shareLabel[2],4,2);
    layout->addWidget(shareLabel[3],5,2);

    layout->addWidget(shareSlider[0],2,3);
    layout->addWidget(shareSlider[1],3,3);
    layout->addWidget(shareSlider[2],4,3);
    layout->addWidget(shareSlider[3],5,3);

    setLayout(layout);
}

void ConfigTabFour::createUI(void)
{
    shareCheckBox[0] = new QCheckBox(tr("ko³o"));
    shareCheckBox[1] = new QCheckBox(tr("kwadrat"));
    shareCheckBox[2] = new QCheckBox(tr("trójk¹t"));
    shareCheckBox[3] = new QCheckBox(tr("prostok¹t"));

    for(int i = 0; i < figureCount; i++)
    {
        checkBoxGroup->addButton(shareCheckBox[i]);
        shareCheckBox[i]->setChecked(true);
        shareLabel[i] = new QLabel("100");
        shareLabel[i]->setFixedSize(30,15);
        shareSlider[i] = new ShareSlider();
    }


    percentageShareLabel = new QLabel(tr("Procentowy udzia³"));
    percentageShareLabel->setFixedSize(100,15);
}

void ConfigTabFour::cancelChanges(void)
{
    for(int i = 0; i < figureCount; i++)
    {
        shareCheckBox[i]->setChecked(figures[i].checked);
        checkBoxChange(i,figures[i].checked);
        shareSlider[i]->setValue(figures[i].procent);
    }
}

void ConfigTabFour::updateChanges(void)
{
    for(int i = 0; i < figureCount; i++)
    {
        figures[i].checked = shareCheckBox[i]->isChecked();
        figures[i].procent = shareSlider[i]->value();
    }
}

ConfigData ConfigTabFour::getConfigData(ConfigData data)
{
    for(int i = 0; i < figureCount; i++)
        data.figures[i] = this->figures[i];

    return data;
}

void ConfigTabFour::loadConfigData(ConfigData data)
{
    for(int i = 0; i < figureCount; i++)
        this->figures[i] = data.figures[i];

    cancelChanges();
}

void ConfigTabFour::checkBoxChange(int checkBoxNumber, bool isChecked)
{
    switch(isChecked)
    {
        case false:
            shareLabel[checkBoxNumber]->setEnabled(false);
            shareSlider[checkBoxNumber]->setEnabled(false);
        break;

        case true:
            shareLabel[checkBoxNumber]->setEnabled(true);
            shareSlider[checkBoxNumber]->setEnabled(true);
        break;
    }
}
