#ifndef CONFIGTAB_H
#define CONFIGTAB_H

#include <QWidget>
#include "globalne.h"

class ConfigTab : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigTab(QWidget *parent = 0);

    virtual void cancelChanges(void)=0;
    virtual void updateChanges(void)=0;
    virtual ConfigData getConfigData(ConfigData)=0;
    virtual void loadConfigData(ConfigData)=0;
    
signals:
    
public slots:
    
};

#endif // CONFIGTAB_H
