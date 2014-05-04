#ifndef CONFIGTABTHREE_H
#define CONFIGTABTHREE_H

#include <QtGui>

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include "configtab.h"

class ConfigTabThree : public ConfigTab
{
    Q_OBJECT

public:

    explicit ConfigTabThree(QWidget *parent = 0);

    void cancelChanges(void);
    void updateChanges(void);
    ConfigData getConfigData(ConfigData);
    void loadConfigData(ConfigData);

private:

    int tabuListSize;
    int tabuListTime;

    QGridLayout *layout;
    QLabel *tabuListSizeLabel;
    QLineEdit *tabuListSizeLineEdit;

    QLabel *tabuListTimeLabel;
    QLineEdit *tabuListTimeLineEdit;

    void createUI(void);
    void createLayout(void);
};

#endif // CONFIGTABTHREE_H
