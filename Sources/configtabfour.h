#ifndef CONFIGTABFOUR_H
#define CONFIGTABFOUR_H

#include <QtGui>
#include "configtab.h"
#include "globalne.h"

class CheckBoxGroup : public QButtonGroup
{
    Q_OBJECT

public:
    explicit CheckBoxGroup(QWidget *parent = 0);

public slots:

    void buttonClick(QAbstractButton* button);

signals:

    void checkBoxClicked(int,bool);
};

class ShareSlider : public QSlider
{
public:

    explicit ShareSlider(QWidget *parent = 0);
};

class ConfigTabFour : public ConfigTab
{
    Q_OBJECT

public:

    explicit ConfigTabFour(QWidget *parent = 0);

    void cancelChanges(void);
    void updateChanges(void);
    ConfigData getConfigData(ConfigData);
    void loadConfigData(ConfigData);

private:

    static const int figureCount = 4;

    FigureData figures[figureCount];

    QGridLayout* layout;

    QCheckBox* shareCheckBox[figureCount];
    QLabel *shareLabel[figureCount];
    ShareSlider* shareSlider[figureCount];
    CheckBoxGroup* checkBoxGroup;

    QLabel *percentageShareLabel;

    void createUI(void);
    void createLayout(void);

private slots:

    void checkBoxChange(int,bool);
};

#endif // CONFIGTABFOUR_H
