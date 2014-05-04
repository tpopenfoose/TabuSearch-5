#ifndef CONFIGTAB1_H
#define CONFIGTAB1_H

#include <QtGui>
#include "configtab.h"
#include "globalne.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>


class ConfigTabOne : public ConfigTab
{
    Q_OBJECT

public:

    explicit ConfigTabOne(QWidget *parent = 0);

    void cancelChanges(void);
    void updateChanges(void);
    ConfigData getConfigData(ConfigData);
    void loadConfigData(ConfigData);

private:

    int width;
    int height;
    int size;

    QGridLayout *layout;

    QLabel *widthLabel;
    QLabel *heightLabel;
    QLabel *sizeLabel;

    QLineEdit *widthLineEdit;
    QLineEdit *heightLineEdit;
    QLineEdit *sizeLineEdit;

    void createUI(void);
    void createLayout(void);
};

#endif // CONFIGTAB1_H
