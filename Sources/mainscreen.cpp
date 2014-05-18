#include <QApplication>
#include <QDesktopWidget>

#include "mainscreen.h"
#include "tasklayout.h"
#include "taskbutton.h"
#include "files.h"

MainScreen::MainScreen(QWidget *parent):
    QScrollArea(parent)
{
    setWidgetResizable(true);
    m_screen_size = QApplication::desktop()->availableGeometry();

    create_inner_screen();

    m_button_group.reset(new QButtonGroup);
    add_button();

    setWidget(m_inner_screen.get());

    connect(m_button_group.get() , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(button_click(QAbstractButton*)));
}

void MainScreen::add_button()
{
    TaskButton *l_button = new TaskButton();
    m_main_layout->addWidget(l_button);
    m_button_group->addButton(l_button);
}

void MainScreen::create_inner_screen()
{
    m_inner_screen.reset(new QWidget(this));
    m_main_layout.reset(new TaskLayout(m_screen_size.width()));
    m_inner_screen->setLayout(m_main_layout.get());
    m_inner_screen->setMaximumWidth(m_screen_size.width()-19);
}

void MainScreen::add_instance()
{
    add_button();
    m_task_list.emplace_back(new Task(this));
}

void MainScreen::delete_instance(Task* p_task)
{
    std::unique_ptr<Task> l_task(p_task);
    auto l_element = std::find(m_task_list.begin(), m_task_list.end(), l_task);
    int l_index = l_element - m_task_list.begin();

    std::shared_ptr<QPushButton> l_button((QPushButton*)(m_button_group->buttons().at(l_index)));
    m_button_group->removeButton(l_button.get());
    m_main_layout->removeWidget(l_button.get());
    l_element->release();
    m_task_list.erase(l_element);
}

bool MainScreen::only_one_button()
{
    return (m_button_group->buttons().size() == 1) ? true : false;
}

void MainScreen::button_click(QAbstractButton* p_button)
{
    if(instance_exist(p_button))
        get_task(p_button).show_window();

    else {
        p_button->setIcon(QIcon(calculate_png.c_str()));
        add_instance();
    }
}

bool MainScreen::instance_exist(QAbstractButton* p_button)
{
    return ((get_position(p_button)+1) == m_button_group->buttons().size()) ? false : true;
}

const Task &MainScreen::get_task(QAbstractButton* p_button)
{
    return *m_task_list[get_position(p_button)];
}

int MainScreen::get_position(QAbstractButton* p_button)
{
    return m_button_group->buttons().indexOf(p_button,0);
}
