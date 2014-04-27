#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <QtGui>

#include "globalne.h"
#include <memory>
#include <result.h>

class TaskThread;
class Inserter;

struct TabuListElement
{
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
    std::unique_ptr<Result> generateFirstResult(std::unique_ptr<Result> p_result);
    void clear(void);
    std::unique_ptr<Result> optimized(std::unique_ptr<Result> p_result);

private:

    int column_count;
    int line_count;
    int figures_count;
    int permutation_count;

    Inserter *inserter;

    std::vector<std::shared_ptr<Shape>> input;
    std::vector<std::shared_ptr<Shape>> result;

    QVector<TabuListElement> TabuList;
    QVector<TabuListElement> PreTabuList;

    QVector< std::vector<std::shared_ptr<Shape>> > Baza_output;
    QVector< std::vector<std::shared_ptr<Shape>> > Baza_input;
    QVector< std::vector<std::shared_ptr<Shape>> > BazaTabu_input;
    QVector< std::vector<std::shared_ptr<Shape>> > BazaTabu_output;

    void calculateFigures();

    void permutate(void);

    void tabulist_check(void);

    void aspiration(void);

    int wasteSum(std::vector<std::shared_ptr<Shape>>);

    bool tabu(TabuListElement);
    void tabulist_calculate(void);

    std::unique_ptr<Result> m_result;

    TaskThread* TaskThreadParent;



signals:

    void actual_count(int);
    void stats(int,int,int);
    
public slots:
    
};

#endif // TABUSEARCH_H
