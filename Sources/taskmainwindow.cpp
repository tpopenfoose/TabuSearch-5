#include "taskmainwindow.h"
#include "tasklayout.h"
#include "task.h"
#include "taskbuttongroup.h"
#include "taskbutton.h"
#include "configwindow.h"
#include "board.h"
#include "tabusearch.h"
#include "inserter.h"
#include "taskthread.h"
#include <QMessageBox>
#include <QScrollArea>
#include <QFormLayout>
#include <QDockWidget>
#include <QAction>
#include <QFileDialog>
#include "sharedmemory.h"
#include "files.h"
//#include <QSignalTransition>

#include <iostream>
using namespace std;

//extern SharedMemory memory;

TaskMainWindow::TaskMainWindow(QObject *parent)
{
    setMinimumSize(600,600);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint);
    Taskparent = (Task*)parent;
    save = true;

    createScrollArea();
    createDockBoxes();
    createToolBar();
    createConnections();
}

void TaskMainWindow::createDockBoxes(void)
{
    createStatusBox();
    createProgresBox();

    setCorner(Qt::BottomRightCorner,Qt::RightDockWidgetArea);
    setDockNestingEnabled(false);
}

void TaskMainWindow::createScrollArea(void)
{
    QScrollArea *scrollarea = new QScrollArea;
    scrollarea->setMinimumWidth(500);
    scrollarea->setWidgetResizable(true);

    QWidget *scrollareawidget = new QWidget;

    QFormLayout *scrollarealayout = new QFormLayout(scrollareawidget);

    resultlabel1 = new QLabel("Pierwszy Wynik");
    resultlabel1->setFixedSize(120,30);
    resultlabel1->hide();
    resultlabel2 = new QLabel("Ostatni Wynik");
    resultlabel2->setFixedSize(120,30);
    resultlabel2->hide();
    scrollarealayout->addRow(resultlabel1,Taskparent->board1);
    scrollarealayout->addRow(resultlabel2,Taskparent->board2);

    scrollarea->setWidget(scrollareawidget);

    setCentralWidget(scrollarea);
}

void TaskMainWindow::createStatusBox(void)
{
    QDockWidget *statusbox = new QDockWidget;

    statusbox->setFeatures(QDockWidget::NoDockWidgetFeatures);
    statusbox->setFixedWidth(100);
    QWidget *titleWidget = new QWidget(this);
    statusbox->setTitleBarWidget( titleWidget );

    QWidget *statusboxwidget = new QWidget;
    QVBoxLayout *statusboxlayout = new QVBoxLayout(statusboxwidget);

    QLabel *statusboxlabel1 = new QLabel(tr("Pierwsze"));
    statusboxlabel1->setFixedSize(90,15);

    QLabel *statusboxlabel2 = new QLabel(tr("Ilość figur:"));
    statusboxlabel2->setFixedSize(90,15);

    lcd1 = new QLCDNumber;

    QLabel *statusboxlabel3 = new QLabel(tr("Procent skrawków:"));
    statusboxlabel3->setFixedSize(90,15);

    lcd2 = new QLCDNumber;

    QLabel *statusboxlabel4 = new QLabel(tr("Ostatnie"));
    statusboxlabel4->setFixedSize(90,15);

    QLabel *statusboxlabel5 = new QLabel(tr("Ilość figur:"));
    statusboxlabel5->setFixedSize(90,15);

    lcd3 = new QLCDNumber;

    QLabel *statusboxlabel6 = new QLabel(tr("Procent skrawków:"));
    statusboxlabel6->setFixedSize(90,15);

    lcd4 = new QLCDNumber;

    statusboxlayout->addWidget(statusboxlabel1);
    statusboxlayout->addWidget(statusboxlabel2);
    statusboxlayout->addWidget(lcd1);
    statusboxlayout->addWidget(statusboxlabel3);
    statusboxlayout->addWidget(lcd2);
    statusboxlayout->addWidget(statusboxlabel4);
    statusboxlayout->addWidget(statusboxlabel5);
    statusboxlayout->addWidget(lcd3);
    statusboxlayout->addWidget(statusboxlabel6);
    statusboxlayout->addWidget(lcd4);
    statusbox->setWidget(statusboxwidget);

    addDockWidget(Qt::RightDockWidgetArea,statusbox,Qt::Vertical);
}

void TaskMainWindow::createProgresBox(void)
{
    QDockWidget *progressbox = new QDockWidget;

    progressbox->setFeatures(QDockWidget::NoDockWidgetFeatures);
    progressbox->setFixedHeight(25);
    QWidget* titleWidget = new QWidget(this);
    progressbox->setTitleBarWidget( titleWidget );

    QWidget *progressboxwidget = new QWidget;
    QHBoxLayout*progressboxlayout = new QHBoxLayout(progressboxwidget);

    ETL = new QLabel;
    ETL->setFixedHeight(15);

    progressbar= new QProgressBar(progressboxwidget);
    progressbar->setRange(0,100);
    progressbar->setValue(0);

    progressbar->setFixedHeight(15);

    progressboxlayout->addWidget(progressbar);
    progressboxlayout->addWidget(ETL);
    progressbox->setWidget(progressboxwidget);

    addDockWidget(Qt::BottomDockWidgetArea,progressbox,Qt::Horizontal);
}

void TaskMainWindow::createConnections(void)
{
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save_Action()));
    connect(loadAction,SIGNAL(triggered()),this,SLOT(load_Action()));

    connect(configAction,SIGNAL(triggered()),this,SLOT(config_Action()));
    connect(randomAction,SIGNAL(triggered()),this,SLOT(random_Action()));
    connect(startAction,SIGNAL(triggered()),this,SLOT(start_Action()));
    connect(pauseAction,SIGNAL(toggled(bool)),this,SLOT(pause_Action(bool)));
    connect(databaseAction,SIGNAL(triggered()),this,SLOT(dataBase_Action()));
    connect(clearAction,SIGNAL(triggered()),this,SLOT(clear_Action()));

    connect(minimizeAction,SIGNAL(triggered()),this,SLOT(hide()));
    connect(maximizeAction,SIGNAL(toggled(bool)),this,SLOT(maximize_Action(bool)));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(exit_Action()));

    connect(Taskparent->taskthread,SIGNAL(finished()),this,SLOT(thread_finished()));
}

void TaskMainWindow::createToolBar(void)
{
    createActions();
    toolbar = new QToolBar(this);

    toolbar->addAction(saveAction);
    toolbar->addAction(loadAction);
    toolbar->addSeparator();
    toolbar->addAction(configAction);
    toolbar->addAction(randomAction);
    toolbar->addAction(startAction);
    toolbar->addAction(pauseAction);
    toolbar->addSeparator();
    toolbar->addAction(databaseAction);
    toolbar->addAction(clearAction);
    toolbar->addSeparator();
    toolbar->addAction(minimizeAction);
    toolbar->addAction(maximizeAction);
    toolbar->addAction(exitAction);
    toolbar->setIconSize(QSize(40,40));
    toolbar->setMovable(false);

    addToolBar(Qt::TopToolBarArea,toolbar);
}

void TaskMainWindow::createActions(void)
{
    saveAction = new QAction(QIcon(save_png.c_str()),tr("Zapisz"), this);
    saveAction->setEnabled(false);
    loadAction = new QAction(QIcon(load_png.c_str()),tr("Wczytaj"), this);

    configAction = new QAction(QIcon(config_png.c_str()),tr("Konfiguracja"), this);
    randomAction = new QAction(QIcon(random_png.c_str()),tr("Generuj Poczatkowe rozwiÄ…zanie"), this);
    startAction = new QAction(QIcon(play_png.c_str()),tr("Start"), this);
    startAction->setEnabled(false);
    pauseAction = new QAction(QIcon(pausesmall_png.c_str()),tr("Pauza"), this);
    pauseAction->setEnabled(false);
    pauseAction->setCheckable(true);

    databaseAction = new QAction(QIcon(database_png.c_str()),tr("Baza Danych"), this);
    databaseAction->setEnabled(false);
    clearAction = new QAction(QIcon(clear_png.c_str()),tr("WyczyĹ›Ä‡"), this);
    clearAction->setEnabled(false);

    minimizeAction = new QAction(QIcon(hide_png.c_str()),tr("Minimalizuj"), this);
    maximizeAction = new QAction(QIcon(maximize_png.c_str()),tr("Maksymalizuj"), this);
    maximizeAction->setCheckable(true);
    exitAction = new QAction(QIcon(exit_png.c_str()),tr("Zamknij"), this);
}

void TaskMainWindow::save_Action(void)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("TabuSearch File (*.tbf)"));

    cout<<"filename: "<<fileName.toStdString()<<endl;

    if(!fileName.isEmpty())
    {
        Taskparent->file = new QFile(fileName);
        Taskparent->file->open(QIODevice::WriteOnly| QIODevice::Text);

        //save_data();

        Taskparent->file->close();

        save = true;
    }
}

void TaskMainWindow::load_Action(void)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("TabuSearch File (*.tbf)"));
    //cout<<fileName.toStdString()<<endl;

    if(!fileName.isEmpty())
    {
        Taskparent->file = new QFile(fileName);
        Taskparent->file->open(QIODevice::ReadOnly| QIODevice::Text);

        //read_data();

        Taskparent->file->close();
    }

    save = true;
    saveAction->setEnabled(true);
    startAction->setEnabled(true);
}

void TaskMainWindow::config_Action(void)
{
    Taskparent->config->show();
}

void TaskMainWindow::random_Action(void)
{
    saveAction->setEnabled(false);
    loadAction->setEnabled(false);
    configAction->setEnabled(false);
    randomAction->setEnabled(false);
    startAction->setEnabled(false);
    pauseAction->setEnabled(true);
    //databaseAction->setEnabled(false);
    clearAction->setEnabled(false);

    save = false;
    tsf.data = Taskparent->config->getConfigData();
    Taskparent->taskthread->insert_data(tsf,1);
    Taskparent->taskthread->start();
}

void TaskMainWindow::start_Action(void)
{
    saveAction->setEnabled(false);
    loadAction->setEnabled(false);
    configAction->setEnabled(false);
    randomAction->setEnabled(false);
    startAction->setEnabled(false);
    pauseAction->setEnabled(true);
    //databaseAction->setEnabled(false);
    clearAction->setEnabled(false);

    tsf.data = Taskparent->config->getConfigData();
    Taskparent->taskthread->insert_data(tsf,2);

    Taskparent->taskthread->start();
}

void TaskMainWindow::pause_Action(bool toggle)
{
    if(toggle)
        Taskparent->taskthread->suspend();
    else
        Taskparent->taskthread->resume();

}

void TaskMainWindow::dataBase_Action(void)
{
    //cout<<TSB.size()<<endl;
}

void TaskMainWindow::clear_Action(void)
{
    QMessageBox msgBox;
    msgBox.setText(tr("Uwaga!"));
    msgBox.setInformativeText(tr("Dotyczczasowe dane zostanÄ… utracone?"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    int ret = msgBox.exec();

    switch (ret) {
       case QMessageBox::Ok:

        saveAction->setEnabled(false);
        loadAction->setEnabled(true);
        configAction->setEnabled(true);
        randomAction->setEnabled(true);
        startAction->setEnabled(false);
        pauseAction->setEnabled(false);
        //databaseAction->setEnabled(false);
        clearAction->setEnabled(false);

        Taskparent->board1->hide();
        Taskparent->board2->hide();

        resultlabel1->hide();
        resultlabel2->hide();

        lcd1->display(0);
        lcd3->display(0);

        saveAction->setEnabled(false);
        startAction->setEnabled(false);

        progressbar->setValue(0);

       break;

       case QMessageBox::Cancel:
       break;
    }
}

void TaskMainWindow::maximize_Action(bool toggle)
{
    if(toggle)
        showMaximized();
    else
        showNormal();

}

void TaskMainWindow::exit_Action(void)
{
    //if(memory.onlyOneButton())
    if(SharedMemory::Instance()->onlyOneButton())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Nie mozna usunÄ…c pierwszego okna."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        if(Taskparent->taskthread->isRunning())
        {
            QMessageBox msgBox;
            msgBox.setText(tr("TrwajÄ… obliczenia."));
            msgBox.setInformativeText(tr("Czy chcesz zatrzymaÄ‡?"));
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();

            switch (ret) {

               case QMessageBox::Ok:
                this->close();
                delete_task();
               break;

               case QMessageBox::Cancel:
               break;
            }
        }
        else
        {
            if(save)
            {
                this->close();
                delete_task();
            }

            else
            {
                 QMessageBox msgBox;
                 msgBox.setText(tr("Zmiany zostanÄ… utracone."));
                 msgBox.setInformativeText(tr("Czy chcesz zapisaÄ‡?"));
                 msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
                 msgBox.setDefaultButton(QMessageBox::Save);
                 int ret = msgBox.exec();

                 switch (ret) {

                    case QMessageBox::Save:
                     saveAction->trigger();
                     this->close();
                     delete_task();
                    break;

                    case QMessageBox::Discard:
                     this->close();
                     delete_task();
                    break;

                    case QMessageBox::Cancel:
                    break;
                }
            }
        }
    }
}
/*
void TaskMainWindow::save_data(void)
{
    QTextStream stream(Taskparent->file);
    QString str;
    //stream<<TSB.isEmpty()<<endl;
    stream<<result.isEmpty()<<endl;

    str+=QString::number(tsf.data.width,10);
    str+=";";
    str+=QString::number(tsf.data.height,10);
    str+=";";
    str+=QString::number(tsf.data.size,10);
    str+=";";
    str+=QString::number(tsf.data.procent,10);
    str+=";";
    str+=QString::number(tsf.data.iteration,10);
    str+=";";
    str+=QString::number(tsf.data.tabusize,10);
    str+=";";
    str+=QString::number(tsf.data.tabutime,10);
    str+=";";

    stream<<str<<endl;
    stream<<QString::number(tsf.all.size(),10)<<endl;

    for(int i = 0;i<tsf.all.size();i++)
    {
        str.clear();
        str+=QString::number(tsf.all[i].x,10);
        str+=";";
        str+=QString::number(tsf.all[i].y,10);
        str+=";";
        str+=QString::number(tsf.all[i].figureName,10);
        str+=";";
        str+=QString::number(tsf.all[i].pozycja,10);

        stream<<str<<endl;
    }

    stream<<QString::number(tsf.result.size(),10)<<endl;

    for(int i = 0;i<tsf.result.size();i++)
    {
        str.clear();
        str+=QString::number(tsf.result[i].x,10);
        str+=";";
        str+=QString::number(tsf.result[i].y,10);
        str+=";";
        str+=QString::number(tsf.result[i].figureName,10);
        str+=";";
        str+=QString::number(tsf.result[i].pozycja,10);

        stream<<str<<endl;
    }

    stream<<QString::number(tsf.rest.size(),10)<<endl;

    for(int i = 0;i<tsf.rest.size();i++)
    {
        str.clear();
        str+=QString::number(tsf.rest[i].x,10);
        str+=";";
        str+=QString::number(tsf.rest[i].y,10);
        str+=";";
        str+=QString::number(tsf.rest[i].figureName,10);
        str+=";";
        str+=QString::number(tsf.rest[i].pozycja,10);

        stream<<str<<endl;
    }

    if(!result.isEmpty())
    {
        stream<<result.size()<<endl;

        for(int i = 0; i < result.size(); i++)
        {
            str.clear();
            str+=QString::number(result[i].x,10);
            str+=";";
            str+=QString::number(result[i].y,10);
            str+=";";
            str+=QString::number(result[i].figureName,10);
            str+=";";
            str+=QString::number(result[i].pozycja,10);

            stream<<str<<endl;
        }

        stream<<endl<<endl;
    }*/
/*
    if(!TSB.isEmpty())
    {
        stream<<TSB.size()<<endl;

        for(int i = 0; i < TSB.size(); i++)
        {
            stream<<TSB[i].size()<<endl;

            for(int j = 0; j < TSB[i].size(); j++)
            {
                str.clear();
                str+=QString::number(TSB[i][j].x,10);
                str+=";";
                str+=QString::number(TSB[i][j].y,10);
                str+=";";
                str+=QString::number(TSB[i][j].figureName,10);
                str+=";";
                str+=QString::number(TSB[i][j].pozycja,10);

                stream<<str<<endl;
            }
        }
        stream<<endl<<endl;

        for(int i = 0; i < TSB.size(); i++)
        {
            stream<<TSB[i].size()<<endl;
        }
    }
    *//*
}

void TaskMainWindow::read_data(void)
{
    QTextStream in(Taskparent->file);
    QString line;
    TSF temp;
    Figure ctemp;
    bool ok;
    int max;
    bool isTSBEmpty = in.readLine().toInt();
    cout<<"czy drugi pusty?: "<<isTSBEmpty<<endl;

    line = in.readLine();

    temp.data.width = line.section(';',0,0).toInt(&ok,10);
    temp.data.height = line.section(';',1,1).toInt(&ok,10);
    temp.data.size = line.section(';',2,2).toInt(&ok,10);
    temp.data.procent = line.section(';',3,3).toInt(&ok,10);
    temp.data.iteration = line.section(';',4,4).toInt(&ok,10);
    temp.data.tabusize = line.section(';',5,5).toInt(&ok,10);
    temp.data.tabutime = line.section(';',6,6).toInt(&ok,10);

    Taskparent->config->loadConfig(temp.data);

    line = in.readLine();

    max = line.toInt(&ok,10);

    for(int i = 0; i < max; i++)
    {
        line = in.readLine();
        ctemp.x = line.section(';',0,0).toInt(&ok,10);
        ctemp.y = line.section(';',1,1).toInt(&ok,10);
        ctemp.figureName = (FigureName)line.section(';',2,2).toInt(&ok,10);
        ctemp.pozycja = line.section(';',3,3).toInt(&ok,10);

        temp.all.push_back(ctemp);
    }

     line = in.readLine();
     max = line.toInt(&ok,10);

     for(int i = 0;i<max;i++)
     {
         line = in.readLine();
         ctemp.x = line.section(';',0,0).toInt(&ok,10);
         ctemp.y = line.section(';',1,1).toInt(&ok,10);
         ctemp.figureName = (FigureName)line.section(';',2,2).toInt(&ok,10);
         ctemp.pozycja = line.section(';',3,3).toInt(&ok,10);

         temp.result.push_back(ctemp);
     }

     line = in.readLine();
     max = line.toInt(&ok,10);

     for(int i = 0;i<max;i++)
     {
         line = in.readLine();
         ctemp.x = line.section(';',0,0).toInt(&ok,10);
         ctemp.y = line.section(';',1,1).toInt(&ok,10);
         ctemp.figureName = (FigureName)line.section(';',2,2).toInt(&ok,10);
         ctemp.pozycja = line.section(';',3,3).toInt(&ok,10);

         temp.rest.push_back(ctemp);
     }

     tsf = temp;
     if(!isTSBEmpty)
     {
         int result_size = in.readLine().toInt();

         result.clear();
         for(int i = 0; i < result_size; i++)
         {

             line = in.readLine();

             ctemp.x = line.section(';',0,0).toInt(&ok,10);
             ctemp.y = line.section(';',1,1).toInt(&ok,10);
             ctemp.figureName = (FigureName)line.section(';',2,2).toInt(&ok,10);
             ctemp.pozycja = line.section(';',3,3).toInt(&ok,10);

             result.push_back(ctemp);
         }
     }

     lcd1->display(tsf.result.size());
     lcd2->display(waste(tsf.result));
     Taskparent->board1->paintBoard(tsf);
     Taskparent->board1->show();
     resultlabel1->show();

     if(!isTSBEmpty)
     {
         TSF temptsf = tsf;
         temptsf.result = result;
         Taskparent->board2->paintBoard(temptsf);
         Taskparent->board2->show();
         resultlabel2->show();
         lcd3->display(temptsf.result.size());
         lcd4->display(waste(temptsf.result));
     }
}
*/
void TaskMainWindow::delete_task(void)
{
    SharedMemory::Instance()->deleteInstance(Taskparent);
}

void TaskMainWindow::thread_finished(void)
{
    int option = Taskparent->taskthread->option;

    switch (option)
    {
        case 1:
            tsf = Taskparent->taskthread->tsf;
            lcd1->display((int)tsf.result.size());
            lcd2->display(waste(tsf.result));

            saveAction->setEnabled(true);
            loadAction->setEnabled(true);
            configAction->setEnabled(true);
            randomAction->setEnabled(true);
            startAction->setEnabled(true);
            pauseAction->setEnabled(false);
            clearAction->setEnabled(true);

            Taskparent->board1->paintBoard(tsf);
            Taskparent->board1->show();
            resultlabel1->show();

        break;

        case 2:

            TSF temptsf = tsf;
            result = Taskparent->taskthread->result;
            temptsf.result = result;
            Taskparent->board2->paintBoard(temptsf);
            lcd3->display((int)temptsf.result.size());
            lcd4->display(waste(temptsf.result));

            saveAction->setEnabled(true);
            loadAction->setEnabled(true);
            configAction->setEnabled(true);
            randomAction->setEnabled(true);
            startAction->setEnabled(true);
            pauseAction->setEnabled(false);
            clearAction->setEnabled(true);

            resultlabel2->show();
            Taskparent->board2->show();

            Taskparent->file = new QFile("temp.tbf");
            Taskparent->file->open(QIODevice::WriteOnly| QIODevice::Text);
            //save_data();
            Taskparent->file->close();

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

    progressbar->setValue(progress);

    int etl = full_time - sec;
    int etl_min = etl/60;
    int etl_sec = etl - (etl_min*60);
    ETL->setText("ETL: "+QString::number(etl_min,10)+" m "+QString::number(etl_sec,10)+" s");
}

int TaskMainWindow::waste(std::vector<std::shared_ptr<Shape>> v)
{
    //cout<<"v: "<<v.size()<<endl;
   int all = tsf.data.height * tsf.data.width;

   int sum = 0;

   for(auto & iter : v)
       sum += iter->get_area(tsf.data.size);

   float p = (float)(all-sum)/all;


   return 100*p;
}
