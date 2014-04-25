#ifndef CONFIGTABTWO_H
#define CONFIGTABTWO_H

#include <QtGui>
#include "configtab.h"
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>

class ConfigTabTwo : public ConfigTab
{
    Q_OBJECT

public:

    explicit ConfigTabTwo(QWidget *parent = 0);

    void cancelChanges(void);
    void updateChanges(void);
    ConfigData getConfigData(ConfigData);
    void loadConfigData(ConfigData);

private:

    int iterationCount;
    int changeCount;

    QGridLayout *layout;

    QLabel *iterationLabel;
    QLabel *chargePercentageLabel;

    QLineEdit *iterationLineEdit;
    QSlider *chargePercentageSlider;

    void createUI(void);
    void createLayout(void);

private slots:

    void sliderChange(int);
};

#endif // CONFIGTABTWO_H
