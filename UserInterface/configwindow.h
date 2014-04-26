#ifndef CONFIG_H
#define CONFIG_H

#include <QtGui>
#include "globalne.h"
#include "configtab.h"
#include <QStackedLayout>
#include <QTabBar>
#include <QPushButton>
#include <QFrame>

class ConfigWindow : public QFrame
{
    Q_OBJECT
    
public:

    explicit ConfigWindow (QWidget *parent = 0);
    ConfigData getConfigData(void);
    void loadConfig(ConfigData);
    
private:

    static const int tabsCount = 3;

    QStackedLayout *layouts;
    QGridLayout *mainlayout;

    ConfigTab* tabs[tabsCount];
    QTabBar *tabBar;

    QPushButton *cancelButton;
    QPushButton *okButton;

    void createMainLayout(void);
    void createMainUI(void);
    void createConnections(void);
    void readData(void);

public slots:



private slots:

    void cancelAction(void);
    void okAction(void);
    void tabChange(int);

};

#endif // CONFIG_H
