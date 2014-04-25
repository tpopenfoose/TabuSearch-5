#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <QtGui>
#include "globalne.h"
#include <QMainWindow>
#include <QAbstractButton>

class Task;
class TaskButtonGroup;
class MainScreen;
class TaskLayout;

class SharedMemory
{
public:

    static SharedMemory* Instance();

    void addInstance(void);
    void deleteInstance(Task*);
    void initMainWindow(QMainWindow*);
    void createMainScreen(QWidget*);
    void readScreenSize(void);
    bool instanceExist(QAbstractButton*);
    Task* getTask(QAbstractButton*);
    bool onlyOneButton(void);
    QRect getScreenSize(void);
    void getParameters(int argc, char *argv[]);

protected:
    SharedMemory();

private:

    QList<Task*> taskList;
    TaskButtonGroup* buttonGroup;
    MainScreen *mainscreen;
    TaskLayout *mainlayout;
    QRect screensize;

    static SharedMemory* _instance;
};

#endif // SHAREDMEMORY_H
