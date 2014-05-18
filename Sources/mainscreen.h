#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QtGui>
#include <QScrollArea>
#include <tasklayout.h>
#include <QButtonGroup>
#include <memory>
#include <task.h>
#include <deque>

class MainScreen : public QScrollArea
{
    Q_OBJECT
public:

    MainScreen(QWidget * parent = 0);
    bool onlyOneButton();

private:

    QWidget *innerScreen;
    QRect screensize;
    std::unique_ptr<TaskLayout> m_main_layout;
    std::unique_ptr<QButtonGroup> m_button_group;
    std::deque<std::unique_ptr<Task>> m_task_list;

    bool instanceExist(QAbstractButton*);
    Task* getTask(QAbstractButton*);
    void add_instance();
public slots:
    void buttonClick(QAbstractButton* button);

private slots:

    void deleteInstance(Task* task);

};

#endif // MAINSCREEN_H
