#include "toolbar.h"
#include "files.h"
#include <QMessageBox>
#include <iostream>

ToolBar::ToolBar() : QToolBar()
{
    createActions();

    addAction(saveAction);
    addAction(loadAction);
    addSeparator();
    addAction(configAction);
    addAction(randomAction);
    addAction(startAction);
    addAction(pauseAction);
    addSeparator();
    addAction(databaseAction);
    addAction(clearAction);
    addSeparator();
    addAction(minimizeAction);
    addAction(maximizeAction);
    addAction(exitAction);
    setIconSize(QSize(40,40));
    setMovable(false);

    createConnections();
}

void ToolBar::createActions(void)
{
    saveAction = new QAction(QIcon(save_png.c_str()),tr("Zapisz"), this);
    saveAction->setEnabled(false);
    loadAction = new QAction(QIcon(load_png.c_str()),tr("Wczytaj"), this);

    configAction = new QAction(QIcon(config_png.c_str()),tr("Konfiguracja"), this);
    randomAction = new QAction(QIcon(random_png.c_str()),tr("Generuj Poczatkowe rozwiązanie"), this);
    startAction = new QAction(QIcon(play_png.c_str()),tr("Start"), this);
    startAction->setEnabled(false);
    pauseAction = new QAction(QIcon(pausesmall_png.c_str()),tr("Pauza"), this);
    pauseAction->setEnabled(false);
    pauseAction->setCheckable(true);

    databaseAction = new QAction(QIcon(database_png.c_str()),tr("Baza Danych"), this);
    databaseAction->setEnabled(false);
    clearAction = new QAction(QIcon(clear_png.c_str()),tr("Wyczyść"), this);
    clearAction->setEnabled(false);

    minimizeAction = new QAction(QIcon(hide_png.c_str()),tr("Minimalizuj"), this);
    maximizeAction = new QAction(QIcon(maximize_png.c_str()),tr("Maksymalizuj"), this);
    maximizeAction->setCheckable(true);
    exitAction = new QAction(QIcon(exit_png.c_str()),tr("Zamknij"), this);
}

void ToolBar::createConnections(void)
{
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save_action()));
    connect(loadAction,SIGNAL(triggered()),this,SLOT(load_action()));

    connect(configAction,SIGNAL(triggered()),this,SLOT(config_action()));
    connect(randomAction,SIGNAL(triggered()),this,SLOT(random_action()));
    connect(startAction,SIGNAL(triggered()),this,SLOT(start_action()));
    connect(pauseAction,SIGNAL(toggled(bool)),this,SLOT(pause_action(bool)));

    connect(databaseAction,SIGNAL(triggered()),this,SLOT(dataBase_action()));
    connect(clearAction,SIGNAL(triggered()),this,SLOT(clear_action()));

    connect(minimizeAction,SIGNAL(triggered()),this,SLOT(minimize_action()));
    connect(maximizeAction,SIGNAL(toggled(bool)),this,SLOT(maximize_action(bool)));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(exit_action()));
}

void ToolBar::save_action()
{
    emit save_button_clicked();
}

void ToolBar::load_action()
{
    emit load_button_clicked();
    saveAction->setEnabled(true);
    startAction->setEnabled(true);
}

void ToolBar::random_action()
{
    saveAction->setEnabled(false);
    loadAction->setEnabled(false);
    configAction->setEnabled(false);
    randomAction->setEnabled(false);
    startAction->setEnabled(false);
    pauseAction->setEnabled(true);
    //databaseAction->setEnabled(false);
    clearAction->setEnabled(false);

    emit random_button_clicked();
}

void ToolBar::start_action()
{
    saveAction->setEnabled(false);
    loadAction->setEnabled(false);
    configAction->setEnabled(false);
    randomAction->setEnabled(false);
    startAction->setEnabled(false);
    pauseAction->setEnabled(true);
    //databaseAction->setEnabled(false);
    clearAction->setEnabled(false);

    emit start_button_clicked();
}

void ToolBar::config_action()
{
    emit config_button_clicked();
}

void ToolBar::pause_action(bool p_toggle)
{
    emit pause_button_clicked(p_toggle);
}

void ToolBar::dataBase_action()
{

}

void ToolBar::clear_action()
{
    emit clear_button_clicked();
}

void ToolBar::clear_message_box_button(int p_button)
{
    switch(p_button)
    {
        case QMessageBox::Ok:
            saveAction->setEnabled(false);
            loadAction->setEnabled(true);
            configAction->setEnabled(true);
            randomAction->setEnabled(true);
            startAction->setEnabled(false);
            pauseAction->setEnabled(false);
            //databaseAction->setEnabled(false);
            clearAction->setEnabled(false);
        break;

        case QMessageBox::Cancel:
        break;
    }
}

void ToolBar::minimize_action()
{
    emit minimize_button_clicked();
}

void ToolBar::maximize_action(bool p_toggle)
{
    emit maximize_button_clicked(p_toggle);
}

void ToolBar::exit_action()
{
    emit exit_button_clicked();
}

void ToolBar::thread_finished()
{
    saveAction->setEnabled(true);
    loadAction->setEnabled(true);
    configAction->setEnabled(true);
    randomAction->setEnabled(true);
    startAction->setEnabled(true);
    pauseAction->setEnabled(false);
    clearAction->setEnabled(true);
}
