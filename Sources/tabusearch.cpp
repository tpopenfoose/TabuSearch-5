#include "tabusearch.h"
#include "taskthread.h"
#include "inserter.h"
#include "task.h"
#include "sharedmemory.h"

#include <iostream>

using namespace std;

extern SharedMemory memory;

TabuSearch::TabuSearch(QObject *parent) :
    QObject(parent)
{
    inserter = new Inserter();

    TaskThreadParent = (TaskThread*)this->parent();
}

void TabuSearch::clear(void)
{

}

void TabuSearch::generateFirstResult(ConfigData data)
{
    qsrand((uint)QTime::currentTime().msec());

    tsf.data = data;
    calculateFigures();
    Figure c;
    QVector<Figure> vector;

    for(int i = 0; i < figures_count; i++)
    {
        c.x = 0;
        c.y = 0;
        c.pozycja = qrand() % 4;

        while(true)
        {
            while(true)
            {
                c.figureName = (FigureName)(qrand() % 4);

                if(data.figures[c.figureName].checked)
                    break;
            }

            int prop = (qrand() % 100)+1;

            if(data.figures[c.figureName].procent >= prop)
                break;
        }

        vector.push_back(c);
    }

    tsf.all = vector;

    tsf = inserter->insert(tsf);

    TaskThreadParent->tsf = tsf;
}

void TabuSearch::aspiration(void)
{
    //int max = result.size();
    int min = wasteSum(result);
    int waste;
    int pos = -1;

    for(int i = 0; i < BazaTabu_output.size(); i++)
    {
        waste = wasteSum(BazaTabu_output[i]);
        //if( BazaTabu_output[i].size() > max)
        if( waste < min)
        {
            //max = BazaTabu_output[i].size();
            min = waste;
            pos = i;
        }
    }

    if (pos != -1)
    {
        result = BazaTabu_output[pos];
        input = BazaTabu_input[pos];
    }
}

int TabuSearch::wasteSum(QVector<Figure> v)
{
   int all = tsf.data.height * tsf.data.width;

   int p_kolo = 3.14*(tsf.data.size/2)*(tsf.data.size/2);
   int p_kwadrat = tsf.data.size*tsf.data.size;
   int p_prostokat = tsf.data.size*tsf.data.size*0.66;
   int p_trojkat = 0.5*tsf.data.size*tsf.data.size;

   int sum = 0;

   for( int i = 0; i < v.size(); i++)
   {
       FigureName temp = v[i].figureName;
       switch(temp)
       {
            case kwadrat:
                sum+=p_kwadrat;
            break;

            case kolo:
                sum+=p_kolo;
            break;

            case trojkat:
                sum+=p_trojkat;
            break;

            case prostokat:
                sum+=p_prostokat;
            break;
       }
   }

   float p = (float)(all-sum)/all;

   return 100*p;
}

void TabuSearch::begin(TSF tsf)
{
    //-------------------------------------
    qsrand((uint)QTime::currentTime().msec());
    QDate date = QDate::currentDate();
    QString dateString = date.toString(Qt::ISODate);
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    timeString.remove(QRegExp(":"));
    QString filename = dateString+"_"+timeString+".txt";
    QFile *file = new QFile(filename);
    file->open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream stream(file);
    //-------------------------------------

    this->tsf = tsf;
    calculateFigures();
    TabuList.reserve(tsf.data.tabusize);

    //int max,pos;
    int min,pos,waste;
    input = tsf.all;

    //Base_all.push_back(this->tsf.result);
    //-------------------------------------
    stream<<this->tsf.result.size()<<";"<<wasteSum(this->tsf.result)<<endl;
    //-------------------------------------

    QTime timer;
    timer.start();

    //-------------------------------------
    QTime timer2;
    timer2.start();
    //-------------------------------------
    QMutex	waitMutex;

    for(int i = 0; i < tsf.data.iteration; i++)
    {
        if (TaskThreadParent->m_bToSuspend)
        {
            waitMutex.lock();
            TaskThreadParent->m_waitCondt.wait(&waitMutex);
            waitMutex.unlock();
        }

        emit stats(i,tsf.data.iteration,timer.elapsed());

        permutate();

        tabulist_calculate();

       // max = 0;
        min = 100;
        pos = 0;

        for(int j = 0; j < Baza_output.size(); j++)
        {
            waste = wasteSum(Baza_output[j]);
            //if(Baza_output[j].size() > max)
            if( waste < min)
            {
                min = waste;
                pos = j;
            }

            if( (waste > min) && (TabuList.size() < TabuList.capacity()) )
            {
                TabuList.push_back(PreTabuList[j]);
            }
        }

        input = Baza_input[pos];
        result = Baza_output[pos];
        //Base_all.push_back(result);
        //-------------------------------------
        stream<<result.size()<<";"<<wasteSum(result)<<endl;
        //-------------------------------------

        aspiration();

        Baza_input.clear();
        Baza_output.clear();
        BazaTabu_input.clear();
        BazaTabu_output.clear();
        PreTabuList.clear();
    }

    //Base_all.push_back(result);
    //-------------------------------------
    stream<<result.size()<<";"<<wasteSum(result)<<endl;
    stream<<timer2.elapsed()/1000<<endl;
    file->close();
    //-------------------------------------

    //TaskThreadParent->TSB = Base_all;
    TaskThreadParent->result = result;


    clear();
    emit stats(1,1,timer.elapsed());
    delete file;
}

void TabuSearch::permutate(void)
{
    qsrand((uint)QTime::currentTime().msec());

    int pos1,pos2;

    Figure f;

    TabuListElement el;
    el.pos2=0;

    QVector<Figure> temp = input;

    for(int i = 0; i < permutation_count/2;i++)
    {
        input = temp;

        while(true)
        {
            pos1 = qrand() % input.size();

            do{
                pos2 = qrand() % input.size();
            }while(pos2 == pos1);

            el.kind = true;
            el.pos1 = pos1;
            el.pos2 = pos2;
            el.timeout = tsf.data.tabutime;
            el.k = 0;

            if(!tabu(el))
               break;
        }

        f = input[pos1];
        input[pos1] = input[pos2];
        input[pos2] = f;

        PreTabuList.push_back(el);

        Baza_input.push_back(input);

        TSF temp_tsf;
        temp_tsf.all = input;
        temp_tsf.data = tsf.data;

        Baza_output.push_back(inserter->insert(temp_tsf).result);
    }

    input = temp;

    for(int i = 0; i < permutation_count/2; i++)
    {
        input = temp;

        while(true)
        {
            pos1 = qrand()%input.size();
            pos2 = qrand()%4;

            el.kind = false;
            el.pos1 = pos1;
            el.k = pos2;
            el.timeout = 10;

            if(!tabu(el))
                break;
        }

        input[pos1].pozycja = pos2;

        PreTabuList.push_back(el);

        Baza_input.push_back(input);

        TSF temp_tsf;
        temp_tsf.all = input;
        temp_tsf.data = tsf.data;

        Baza_output.push_back(inserter->insert(temp_tsf).result);
    }

    input = temp;
}

bool TabuSearch::tabu(TabuListElement el)
{
    for(int i = 0;i<TabuList.size();i++)
    {
        if(TabuList[i].kind)
        {
            if((TabuList[i].pos1 == el.pos1 && TabuList[i].pos2 == el.pos2) || (TabuList[i].pos1 == el.pos2 && TabuList[i].pos2 == el.pos1))
                return true;
            else
                return false;
        }
        else
        {
            if(TabuList[i].pos1 == el.pos1 && TabuList[i].k == el.k )
                return true;
            else
                return false;
        }
    }

    return false;
}

void TabuSearch::tabulist_calculate(void)
{
    int pos1,pos2,k;

    Figure f;

    QVector<Figure> temp = input;

    for(int i = 0;i<TabuList.size();)
    {
        if(TabuList[i].timeout > 0)
        {
            input = temp;

            if (TabuList[i].kind)
            {
                pos1 = TabuList[i].pos1;
                pos2 = TabuList[i].pos2;

                f = input[pos1];
                input[pos1] = input[pos2];
                input[pos2] = f;
            }
            else
            {
                pos1 = TabuList[i].pos1;
                k = TabuList[i].k;
                input[pos1].pozycja = k;
            }

            BazaTabu_input.push_back(input);

            TSF temp_tsf;
            temp_tsf.all = input;
            temp_tsf.data = tsf.data;

            BazaTabu_output.push_back(inserter->insert(temp_tsf).result);

            TabuList[i].timeout-=1;
            i++;
        }

        else
        {
            TabuList.remove(i);
        }
    }
    input = temp;
}

void TabuSearch::calculateFigures()
{
    column_count = tsf.data.width/tsf.data.size;

    line_count = tsf.data.height/tsf.data.size;

    figures_count = column_count*line_count + (column_count*line_count)/2;

    float mnoznik = (float)tsf.data.procent/100;
    permutation_count = mnoznik*figures_count;
}

TSF TabuSearch::generateFirstResultCommandLine(ConfigData data)
{
    qsrand((uint)QTime::currentTime().msec());

    tsf.data = data;
    calculateFigures();
    Figure c;
    QVector<Figure> vector;

    for(int i = 0; i < figures_count; i++)
    {
        c.x = 0;
        c.y = 0;
        c.pozycja = qrand() % 4;

        while(true)
        {
            while(true)
            {
                c.figureName = (FigureName)(qrand() % 4);

                if(data.figures[c.figureName].checked)
                    break;
            }

            int prop = (qrand() % 100)+1;

            if(data.figures[c.figureName].procent >= prop)
                break;
        }

        vector.push_back(c);
    }

    tsf.all = vector;

    tsf = inserter->insert(tsf);

    return tsf;
}

TSF TabuSearch::beginCommandLine(TSF tsf , QString path)
{
    //-------------------------------------
    QDate date = QDate::currentDate();
    QString dateString = date.toString(Qt::ISODate);
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    timeString.remove(QRegExp(":"));
    QString filename = "t_"+dateString+"_"+timeString+".txt";
    //cout<<"filename: "<<filename.toStdString()<<endl;
    QDir dir;
    dir.mkpath(path);
    dir.setPath(path);
    QFile *file = new QFile(dir.filePath(filename));
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(file);
    //-------------------------------------

    this->tsf = tsf;
    calculateFigures();
    TabuList.reserve(tsf.data.tabusize);

    int min,pos,waste;
    input = tsf.all;

    //-------------------------------------
    stream<<this->tsf.result.size()<<";"<<wasteSum(this->tsf.result)<<endl;
    //-------------------------------------

    //-------------------------------------
    QTime timer2;
    timer2.start();
    //-------------------------------------

    for(int i = 0; i < tsf.data.iteration; i++)
    {
        permutate();

        tabulist_calculate();

        min = 100;
        pos = 0;

        for(int j = 0; j < Baza_output.size(); j++)
        {
            waste = wasteSum(Baza_output[j]);
            if( waste < min)
            {
                min = waste;
                pos = j;
            }

            if( (waste > min) && (TabuList.size() < TabuList.capacity()) )
            {
                TabuList.push_back(PreTabuList[j]);
            }
        }

        input = Baza_input[pos];
        result = Baza_output[pos];

        //-------------------------------------
        stream<<result.size()<<";"<<wasteSum(result)<<endl;
        //-------------------------------------

        aspiration();

        Baza_input.clear();
        Baza_output.clear();
        BazaTabu_input.clear();
        BazaTabu_output.clear();
        PreTabuList.clear();
    }

    //-------------------------------------
    stream<<result.size()<<";"<<wasteSum(result)<<endl;
    stream<<timer2.elapsed()/1000<<endl;
    file->close();
    //-------------------------------------
    this->tsf.result = result;
    return this->tsf;
}

