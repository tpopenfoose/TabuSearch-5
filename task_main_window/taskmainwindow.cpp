#include "taskmainwindow.h"
#include <QFileDialog>
#include "messagebox.h"

TaskMainWindow::TaskMainWindow()
{
    setMinimumSize(600,600);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint);
    m_save = true;
    m_calculations_in_progress = false;

    create_scroll_area();
    create_dock_boxes();
    create_tool_bar();
    create_connections();
}

void TaskMainWindow::create_dock_boxes(void)
{
    create_status_box();
    create_progres_box();

    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    setDockNestingEnabled(false);
}

void TaskMainWindow::create_scroll_area(void)
{
    m_scroll_area.reset(new ScrollArea());
    setCentralWidget(m_scroll_area.get());
}

void TaskMainWindow::create_status_box(void)
{
    m_status_box.reset(new StatusBox());
    addDockWidget(Qt::RightDockWidgetArea, m_status_box.get(), Qt::Vertical);
}

void TaskMainWindow::create_progres_box(void)
{
    m_progress_box.reset(new ProgressBox());
    addDockWidget(Qt::BottomDockWidgetArea, m_progress_box.get(), Qt::Horizontal);
}

void TaskMainWindow::create_connections(void)
{
    connect(m_toolbar.get(),SIGNAL(save_button_clicked()),this,SLOT(save_action()));
    connect(m_toolbar.get(),SIGNAL(load_button_clicked()),this,SLOT(load_action()));

    connect(m_toolbar.get(),SIGNAL(config_button_clicked()),this,SLOT(config_action()));
    connect(m_toolbar.get(),SIGNAL(random_button_clicked()),this,SLOT(random_action()));
    connect(m_toolbar.get(),SIGNAL(start_button_clicked()),this,SLOT(start_action()));
    connect(m_toolbar.get(),SIGNAL(pause_button_clicked(bool)),this,SLOT(pause_action(bool)));

    connect(m_toolbar.get(),SIGNAL(dataBase_button_clicked()),this,SLOT(data_base_action()));
    connect(m_toolbar.get(),SIGNAL(clear_button_clicked()),this,SLOT(clear_action()));

    connect(m_toolbar.get(),SIGNAL(minimize_button_clicked()),this,SLOT(hide()));
    connect(m_toolbar.get(),SIGNAL(maximize_button_clicked(bool)),this,SLOT(maximize_action(bool)));
    connect(m_toolbar.get(),SIGNAL(exit_button_clicked()),this,SLOT(exit_action()));
    connect(this,SIGNAL(thread_finished()),m_toolbar.get(),SLOT(thread_finished()));
}

void TaskMainWindow::create_tool_bar(void)
{
    m_toolbar.reset(new ToolBar());
    addToolBar(Qt::TopToolBarArea, m_toolbar.get());
}

void TaskMainWindow::save_action()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("TabuSearch File (*.tbf)"));

    if(!fileName.isEmpty())
    {
        //file = new QFile(fileName);
       // file->open(QIODevice::WriteOnly| QIODevice::Text);
        //save_data();
        //file->close();
        m_save = true;
    }
}

void TaskMainWindow::load_action()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("TabuSearch File (*.tbf)"));

    if(!fileName.isEmpty())
    {
        //file = new QFile(fileName);
       // file->open(QIODevice::ReadOnly| QIODevice::Text);
        //read_data();
        //file->close();
    }

    m_save = true;
}

void TaskMainWindow::random_action()
{
    m_save = false;
    emit random_button_clicked();
}

void TaskMainWindow::start_action()
{
    emit start_button_clicked();
}

void TaskMainWindow::data_base_action()
{

}

void TaskMainWindow::config_action()
{
    emit config_button_clicked();
}

void TaskMainWindow::pause_action(bool p_flag)
{
    emit pause_button_clicked(p_flag);
}

void TaskMainWindow::clear_action()
{
    m_msgBox.reset(new DataLoss());

    switch(m_msgBox->exec()) {
        case QMessageBox::Ok:
            emit clear_message_box_button(QMessageBox::Ok);

            m_scroll_area->board1->hide();
            m_scroll_area->board2->hide();
            m_scroll_area->resultlabel1->hide();
            m_scroll_area->resultlabel2->hide();
            m_status_box->lcd1->display(0);
            m_status_box->lcd3->display(0);

            m_progress_box->progressbar->setValue(0);
        break;

        case QMessageBox::Cancel:
            emit clear_message_box_button(QMessageBox::Cancel);
        break;
    }
}

void TaskMainWindow::maximize_action(bool p_toggle)
{
    if(p_toggle)
        showMaximized();
    else
        showNormal();
}

void TaskMainWindow::exit_action()
{
    emit exit_button_clicked();
}

void TaskMainWindow::thread_finished(int p_action)
{
    switch(p_action) {
        case 1:
            m_scroll_area->resultlabel1->show();
        break;

        case 2:
            m_scroll_area->resultlabel2->show();
        break;
    }

    emit thread_finished();
}

void TaskMainWindow::display_result(const Result &p_result, int p_option)
{
    switch(p_option) {
        case 1:
            m_status_box->lcd1->display((int)p_result.getResult().size());
            m_status_box->lcd2->display(p_result.waste());
            m_scroll_area->board1->paintBoard(p_result);
            m_scroll_area->board1->show();
        break;

        case 2:
            m_status_box->lcd3->display((int)p_result.getResult().size());
            m_status_box->lcd4->display(p_result.waste());
            m_scroll_area->board2->paintBoard(p_result);
            m_scroll_area->board2->show();
        break;
    }
}

void TaskMainWindow::update_progress(int value,int all,int time)
{
    int progress = (value*100)/all;
    int sec = time/1000;
    int full_time;
    if(progress == 0)
        full_time = time/10;
    else
        full_time = time/(10*progress);

    m_progress_box->progressbar->setValue(progress);

    int etl = full_time - sec;
    int etl_min = etl/60;
    int etl_sec = etl - (etl_min*60);
    m_progress_box->ETL->setText("ETL: "+QString::number(etl_min,10)+" m "+QString::number(etl_sec,10)+" s");
}

void TaskMainWindow::try_delete_task()
{
    if(m_calculations_in_progress)
        inform_about_calculations();
    else
        try_to_save();
}

void TaskMainWindow::process_exit(bool p_only_button)
{
    if(p_only_button) {
        m_msgBox.reset(new OneTask());
        m_msgBox->exec();
    } else
        try_delete_task();
}

void TaskMainWindow::inform_about_calculations()
{
    m_msgBox.reset(new CalculationsInProgress());

    switch (m_msgBox->exec()) {
        case QMessageBox::Ok:
            close();
            emit delete_task();
        break;

        case QMessageBox::Cancel:
        break;
    }
}

void TaskMainWindow::try_to_save()
{
    if(m_save) {
        close();
        emit delete_task();
    } else {
         m_msgBox.reset(new PossibleDataLoss());

         switch (m_msgBox->exec()) {
            case QMessageBox::Save:
                //saveAction->trigger();
                close();
                emit delete_task();
            break;

            case QMessageBox::Discard:
                close();
                emit delete_task();
            break;

            case QMessageBox::Cancel:
            break;
        }
    }
}
