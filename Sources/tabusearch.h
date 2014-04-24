#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <QtGui>

#include "globalne.h"

class TaskThread;
class Inserter;

struct TabuListElement
{
    bool kind;

    int pos1;

    int pos2;

    int k;

    int timeout;
};

class TabuSearch : public QObject
{
    Q_OBJECT

public:

    explicit TabuSearch(QObject *parent = 0);
    void generateFirstResult(ConfigData data);
    void clear(void);
    void begin(TSF tsf);

    TSF generateFirstResultCommandLine(ConfigData data);
    TSF beginCommandLine(TSF,QString);


private:

    int column_count;
    int line_count;
    int figures_count;
    int permutation_count;

    Inserter *inserter;

    QVector<Figure> input;
    QVector<Figure> result;

    QVector<TabuListElement> TabuList;
    QVector<TabuListElement> PreTabuList;

    QVector< QVector<Figure> > Baza_output;
    QVector< QVector<Figure> > Baza_input;
    QVector< QVector<Figure> > BazaTabu_input;
    QVector< QVector<Figure> > BazaTabu_output;
    //QVector< QVector<Figure> > Base_all;

    void calculateFigures();

    void permutate(void);

    void tabulist_check(void);

    void aspiration(void);

    int wasteSum(QVector<Figure>);

    bool tabu(TabuListElement);
    void tabulist_calculate(void);

    TSF tsf;

    TaskThread* TaskThreadParent;



signals:

    void actual_count(int);
    void stats(int,int,int);
    
public slots:
    
};

#endif // TABUSEARCH_H
