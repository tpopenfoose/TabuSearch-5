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
    bool only_one_button();

private:
    QRect m_screen_size;
    std::unique_ptr<QWidget> m_inner_screen;
    std::unique_ptr<TaskLayout> m_main_layout;
    std::unique_ptr<QButtonGroup> m_button_group;
    std::deque<std::unique_ptr<Task>> m_task_list;

    bool instance_exist(QAbstractButton*p_button);
    const Task& get_task(QAbstractButton*p_button);
    void add_instance();
    void add_button();
    void create_inner_screen();
    int get_position(QAbstractButton* p_button);

public slots:
    void button_click(QAbstractButton* p_button);

private slots:
    void delete_instance(Task* p_task);
};

#endif // MAINSCREEN_H
