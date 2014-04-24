#include "mainwindow.h"
#include "sharedmemory.h"
#include "tabusearch.h"
#include "inserter.h"

#include "QString"
#include <iostream>

using namespace std;

//SharedMemory memory;

void commandLine(char*);

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        commandLine(argv[1]);

        return 0;
    }
    else
    {
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QApplication app(argc, argv);
        Q_INIT_RESOURCE(files);
        MainWindow mainwindow;

        mainwindow.show();

        return app.exec();
    }
}

void save_data(TSF tsf1, TSF tsf2,QString path)
{
    //-------------------------------------
    QDate date = QDate::currentDate();
    QString dateString = date.toString(Qt::ISODate);
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    timeString.remove(QRegExp(":"));
    QString filename = "r_"+dateString+"_"+timeString+".tbf";
    QDir dir;
    dir.mkpath(path);
    dir.setPath(path);
    QFile *file = new QFile(dir.filePath(filename));
    file->open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream stream(file);
    //-------------------------------------
    QString str;

    stream<<tsf2.result.isEmpty()<<endl;

    str+=QString::number(tsf1.data.width,10);
    str+=";";
    str+=QString::number(tsf1.data.height,10);
    str+=";";
    str+=QString::number(tsf1.data.size,10);
    str+=";";
    str+=QString::number(tsf1.data.procent,10);
    str+=";";
    str+=QString::number(tsf1.data.iteration,10);
    str+=";";
    str+=QString::number(tsf1.data.tabusize,10);
    str+=";";
    str+=QString::number(tsf1.data.tabutime,10);
    str+=";";

    for(int i  = 0; i < 4; i++)
    {
        str+=QString::number(tsf1.data.figures[i].checked,10);
        str+=";";
        str+=QString::number(tsf1.data.figures[i].procent,10);
        str+=";";
    }

    stream<<str<<endl;
    stream<<QString::number(tsf1.all.size(),10)<<endl;

    for(int i = 0;i<tsf1.all.size();i++)
    {
        str.clear();
        str+=QString::number(tsf1.all[i].x,10);
        str+=";";
        str+=QString::number(tsf1.all[i].y,10);
        str+=";";
        str+=QString::number(tsf1.all[i].figureName,10);
        str+=";";
        str+=QString::number(tsf1.all[i].pozycja,10);

        stream<<str<<endl;
    }

    stream<<QString::number(tsf1.result.size(),10)<<endl;

    for(int i = 0;i<tsf1.result.size();i++)
    {
        str.clear();
        str+=QString::number(tsf1.result[i].x,10);
        str+=";";
        str+=QString::number(tsf1.result[i].y,10);
        str+=";";
        str+=QString::number(tsf1.result[i].figureName,10);
        str+=";";
        str+=QString::number(tsf1.result[i].pozycja,10);

        stream<<str<<endl;
    }

    stream<<QString::number(tsf1.rest.size(),10)<<endl;

    for(int i = 0;i<tsf1.rest.size();i++)
    {
        str.clear();
        str+=QString::number(tsf1.rest[i].x,10);
        str+=";";
        str+=QString::number(tsf1.rest[i].y,10);
        str+=";";
        str+=QString::number(tsf1.rest[i].figureName,10);
        str+=";";
        str+=QString::number(tsf1.rest[i].pozycja,10);

        stream<<str<<endl;
    }

    if(!tsf2.result.isEmpty())
    {
        stream<<tsf2.result.size()<<endl;

        for(int i = 0; i < tsf2.result.size(); i++)
        {
            str.clear();
            str+=QString::number(tsf2.result[i].x,10);
            str+=";";
            str+=QString::number(tsf2.result[i].y,10);
            str+=";";
            str+=QString::number(tsf2.result[i].figureName,10);
            str+=";";
            str+=QString::number(tsf2.result[i].pozycja,10);

            stream<<str<<endl;
        }

        stream<<endl<<endl;
    }
}

TSF loadData(QFile *file)
{
    QTextStream in(file);
    QString line;
    TSF temp;
    Figure ctemp;
    bool ok;
    int max;
    bool isTSBEmpty = in.readLine().toInt();

    line = in.readLine();
    //cout<<line.toStdString()<<endl;

    temp.data.width = line.section(';',0,0).toInt(&ok,10);
    temp.data.height = line.section(';',1,1).toInt(&ok,10);
    temp.data.size = line.section(';',2,2).toInt(&ok,10);
    temp.data.procent = line.section(';',3,3).toInt(&ok,10);
    temp.data.iteration = line.section(';',4,4).toInt(&ok,10);
    temp.data.tabusize = line.section(';',5,5).toInt(&ok,10);
    temp.data.tabutime = line.section(';',6,6).toInt(&ok,10);

    //cout<<temp.data.width<<endl;

    int end = 7;

    for(int i  = 0; i < 4; i++)
    {
        temp.data.figures[i].checked = line.section(';',end,end).toInt(&ok,10);
        temp.data.figures[i].procent = line.section(';',end+1,end+1).toInt(&ok,10);
        end+=2;
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
/*
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
*/
     return temp;
}

TSF customTSF(TSF tsf,int num,int pos)
{
    int base1 = 20;
    int base2 = 10;
    int base3 = 1;
    int base4 = 2;
    switch (num)
    {
        case 1:
            tsf.data.procent = 5;
            tsf.data.iteration = base1*pow(2,pos-1);
            tsf.data.tabusize = 1;
            tsf.data.tabutime = 5;
        break;

        case 2:
            tsf.data.procent = base2*pos;
            tsf.data.iteration = 50;
            tsf.data.tabusize = 1;
            tsf.data.tabutime = 5;
        break;

        case 3:
            tsf.data.procent = 5;
            tsf.data.iteration = 50;
            tsf.data.tabusize = base3*pos;
            tsf.data.tabutime = 5;
        break;

        case 4:
            tsf.data.procent = 5;
            tsf.data.iteration = 50;
            tsf.data.tabusize = 5;
            tsf.data.tabutime = base4+(2*(pos-1));
        break;
    }

    return tsf;
}

void commandLine(char* parameter)
{
    QString param = QString(parameter);

    int instance_begin;
    int instance_end;

    int test_begin;
    int test_end;

    int subject_begin;
    int subject_end;

    bool ok;
    instance_begin = param.section(';',0,0).toInt(&ok,10);
    instance_end = param.section(';',1,1).toInt(&ok,10);
    subject_begin = param.section(';',2,2).toInt(&ok,10);;
    subject_end = param.section(';',3,3).toInt(&ok,10);;
    test_begin = param.section(';',4,4).toInt(&ok,10);
    test_end = param.section(';',5,5).toInt(&ok,10);

    //cout<<instance_begin<<endl;
    //cout<<instance_end<<endl;
    //cout<<test_begin<<endl;
    //cout<<test_end<<endl;

    QString mainFileName,mainFileNumber,pos;
    QString t1 = "01. Ilosc iteracji";
    QString t2 = "02. Wielkosc sasiedztwa";
    QString t3 = "03. Dlugosc listy Tabu";
    QString t4 = "04. Czas pobytu na Liscie Tabu";
    QString path;

    TSF temp1,temp2;
    TabuSearch *engine = new TabuSearch;
    for(int i = instance_begin; i <= instance_end; i++)
    {

        if(i!=10)
        {
            mainFileNumber = "0"+QString::number(i,10);
            mainFileName = mainFileNumber +".tbf";
        }
        else
        {
            mainFileNumber = "10";
            mainFileName = mainFileNumber +".tbf";
        }

        //cout<<"mainfile: "<<mainFileName.toStdString()<<endl;
        QDir dir;
        dir.setPath("C:/badania/testy/");
        QFile *mainFile = new QFile(dir.filePath(mainFileName));
        mainFile->open(QIODevice::ReadOnly | QIODevice::Text);

        temp1 = loadData(mainFile);

        for(int j = subject_begin; j <= subject_end; j++)
        {
            //cout<<"zagadnienie: "<<j<<endl;
            switch (j)
            {
                case 1:
                    //path+=t1+"\\";
                    //cout<<"case 1"<<endl;
                    for( int k = test_begin; k <= test_end; k++)
                    {
                        if(k!=10)
                            pos= "0"+QString::number(k,10)+"";
                        else
                            pos= "10";

                        //cout<<"pos: "<<pos.toStdString()<<endl;
                        temp1 = customTSF(temp1,j,k);
                        path="C:/badania/"+mainFileNumber+"/"+t1+"/"+pos+"."+QString::number(temp1.data.iteration,10)+"/";
                        //cout<<"path: "<<path.toStdString()<<endl;

                        for(int l = 0; l < 5;l++)
                        {
                            temp2 = engine->beginCommandLine(temp1,path);
                            save_data(temp1,temp2,path);
                        }
                    }
                break;

                case 2:
                    //cout<<"case 2"<<endl;
                    //path+=t2+"\\";
                    for( int k = test_begin; k <= test_end; k++)
                    {
                        if(k!=10)
                            pos= "0"+QString::number(k,10)+"";
                        else
                            pos= "10";

                        //cout<<"pos: "<<pos.toStdString()<<endl;

                        for(int l = 0; l < 5;l++)
                        {
                            temp1 = customTSF(temp1,j,k);
                            path="C:\\badania\\"+mainFileNumber+"\\"+t2+"\\"+pos+"."+QString::number(temp1.data.procent,10)+"\\";
                            //cout<<"path: "<<path.toStdString()<<endl;
                            temp2 = engine->beginCommandLine(temp1,path);
                            save_data(temp1,temp2,path);
                        }
                    }
                break;

                case 3:
                    //cout<<"case 3"<<endl;
                    //path+=t3+"\\";
                    for( int k = test_begin; k <= test_end; k++)
                    {
                        if(k!=10)
                            pos= "0"+QString::number(k,10)+"";
                        else
                            pos= "10";

                        //cout<<"pos: "<<pos.toStdString()<<endl;

                        for(int l = 0; l < 5;l++)
                        {
                            temp1 = customTSF(temp1,j,k);
                            path="C:\\badania\\"+mainFileNumber+"\\"+t3+"\\"+pos+"."+QString::number(temp1.data.tabusize,10)+"\\";
                            //cout<<"path: "<<path.toStdString()<<endl;
                            temp2 = engine->beginCommandLine(temp1,path);
                            save_data(temp1,temp2,path);
                        }
                    }
                break;

                case 4:
                    cout<<"case 4"<<endl;
                    //path+=t4+"\\";
                    for( int k = test_begin; k <= test_end; k++)
                    {
                        if(k!=10)
                            pos= "0"+QString::number(k,10)+"";
                        else
                            pos= "10";

                        cout<<"pos: "<<pos.toStdString()<<endl;

                        for(int l = 0; l < 5;l++)
                        {
                            temp1 = customTSF(temp1,j,k);
                            path="C:\\badania\\"+mainFileNumber+"\\"+t4+"\\"+pos+"."+QString::number(temp1.data.tabutime,10)+"\\";
                            cout<<"path: "<<path.toStdString()<<endl;
                            temp2 = engine->beginCommandLine(temp1,path);
                            save_data(temp1,temp2,path);
                        }
                    }
                break;
            }
        }
    }
}