#ifndef TASK_H
#define TASK_H

#include "globalne.h"
#include "result.h"
#include "configwindow.h"
#include "taskthread.h"
#include "taskmainwindow.h"

#include <QtGui>
#include <memory>

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);
    void show_window(void);
    virtual ~Task();
private:
    QFile *file;
    std::unique_ptr<Result> m_result;
    ConfigWindow *config;
    TaskMainWindow *mainwindow;
    TaskThread *taskthread;
    int m_option;


private slots:
    void random_Action();

    void start_Action();
    void pause_Action(bool toggle);
    void config_Action();
    void delete_task();
    void exit_action();
    void thread_finished(int p_action);
    
signals:

    void finished(int p_action);
    void exit(bool);
    
public slots:
    
};

#endif // TASK_H
