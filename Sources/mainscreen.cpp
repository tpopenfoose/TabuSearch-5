#include "mainscreen.h"
#include "tasklayout.h"
#include "taskbutton.h"
#include <QApplication>
#include <QDesktopWidget>
#include "files.h"
#include <iostream>
#include <algorithm>

MainScreen::MainScreen(QWidget *parent):
    QScrollArea(parent)
{
    setWidgetResizable(true);
    screensize = QApplication::desktop()->availableGeometry();

    innerScreen = new QWidget(this);

    m_main_layout.reset(new TaskLayout(innerScreen, screensize.width()));

    m_button_group.reset(new QButtonGroup);

    innerScreen->setLayout(m_main_layout.get());
    innerScreen->setMaximumWidth(screensize.width()-19);

    TaskButton *button = new TaskButton();
    m_main_layout->addWidget(button);
    m_button_group->addButton(button);

    setWidget(innerScreen);

    connect(m_button_group.get() , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));
}

void MainScreen::add_instance()
{
    TaskButton* button = new TaskButton();
    m_main_layout->addWidget(button);
    m_button_group->addButton(button);
    m_task_list.emplace_back(new Task(this));
}

void MainScreen::deleteInstance(Task* task)
{
    std::unique_ptr<Task> l_task(task);
    auto element = std::find(m_task_list.begin(), m_task_list.end(), l_task);
    int pos = element - m_task_list.begin();

    std::shared_ptr<QPushButton> l_button((QPushButton*)(m_button_group->buttons().at(pos)));
    m_button_group->removeButton(l_button.get());
    m_main_layout->removeWidget(l_button.get());
    element->release();
    m_task_list.erase(element);
}

bool MainScreen::onlyOneButton()
{
    return (m_button_group->buttons().size() == 1) ? true : false;
}

void MainScreen::buttonClick(QAbstractButton* button)
{
    if(instanceExist(button))
        getTask(button)->show_window();

    else
    {
        button->setIcon(QIcon(calculate_png.c_str()));
        add_instance();
    }
}

bool MainScreen::instanceExist(QAbstractButton* button)
{
    int position = m_button_group->buttons().indexOf(button,0);

    return ((position+1) == m_button_group->buttons().size()) ? false : true;
}

Task* MainScreen::getTask(QAbstractButton* button)
{
    int position = m_button_group->buttons().indexOf(button,0);

    return m_task_list[position].get();
}





