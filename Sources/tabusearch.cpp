#include "tabusearch.h"
#include "taskthread.h"
#include "inserter.h"
#include "task.h"
#include "generator.h"

#include <iostream>

using namespace std;

TabuSearch::TabuSearch(TaskThread *parent) :
    QObject()
{
    inserter = new Inserter();

    TaskThreadParent = parent;
}

void TabuSearch::clear(void)
{

}

std::unique_ptr<Result> TabuSearch::generateFirstResult(std::unique_ptr<Result> p_result)
{
    Generator gen;
    p_result->set_result(gen.generate(*p_result));
    p_result = std::move(inserter->insert(std::move(p_result)));
    return p_result;
}

void TabuSearch::aspiration(void)
{
    int min = wasteSum(result);
    int waste;
    int pos = -1;

    for(int i = 0; i < BazaTabu_output.size(); i++)
    {
        waste = wasteSum(BazaTabu_output[i]);
        if( waste < min)
        {
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

int TabuSearch::wasteSum(std::vector<std::shared_ptr<Shape>> v)
{
   int all = m_result->get_height() * m_result->get_width();

   int sum = 0;

   for(auto & iter : v)
       sum += iter->get_area(m_result->get_size());

   float p = (float)(all-sum)/all;

   return 100*p;
}

std::unique_ptr<Result> TabuSearch::optimized(std::unique_ptr<Result> p_result)
{
    m_result = std::move(p_result);
    calculateFigures();
    TabuList.reserve(m_result->get_tabusize());

    int min,pos,waste;
    input = m_result->getAll();

    QTime timer;
    timer.start();
    QMutex	waitMutex;

    for(int i = 0; i < m_result->get_iteration(); i++)
    {
        if (TaskThreadParent->m_bToSuspend)
        {
            waitMutex.lock();
            TaskThreadParent->m_waitCondt.wait(&waitMutex);
            waitMutex.unlock();
        }

        emit stats(i,m_result->get_iteration(),timer.elapsed());

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

        aspiration();

        Baza_input.clear();
        Baza_output.clear();
        BazaTabu_input.clear();
        BazaTabu_output.clear();
        PreTabuList.clear();
    }

    //TaskThreadParent->result = result;

    clear();
    emit stats(1,1,timer.elapsed());

    p_result = std::move(m_result);
    return p_result;
}

void TabuSearch::permutate(void)
{
    qsrand((uint)QTime::currentTime().msec());

    int pos1,pos2;

    TabuListElement el;
    el.pos2=0;

    std::vector<std::shared_ptr<Shape>> temp = input;

    for(int i = 0; i < permutation_count/2;i++)
    {
        input = temp;

        while(true)
        {
            pos1 = qrand() % input.size();

            do{
                pos2 = qrand() % input.size();
            }while(pos2 == pos1);

            el.pos1 = pos1;
            el.pos2 = pos2;
            el.timeout = m_result->get_tabutime();
            el.k = 0;

            if(!tabu(el))
               break;
        }

        std::swap(input[pos1], input[pos2]);

        PreTabuList.push_back(el);

        Baza_input.push_back(input);

        std::unique_ptr<Result> temp_result(new Result(*m_result));
        temp_result->set_result(input);
        temp_result = std::move(inserter->insert(std::move(temp_result)));

        Baza_output.push_back(temp_result->getResult());
    }

    input = temp;
}

bool TabuSearch::tabu(TabuListElement el)
{
    for(int i = 0;i<TabuList.size();i++)
    {
        if((TabuList[i].pos1 == el.pos1 && TabuList[i].pos2 == el.pos2) || (TabuList[i].pos1 == el.pos2 && TabuList[i].pos2 == el.pos1))
            return true;
        else
            return false;
    }

    return false;
}

void TabuSearch::tabulist_calculate(void)
{
    int pos1,pos2;

    std::vector<std::shared_ptr<Shape>> temp = input;

    for(int i = 0;i<TabuList.size();)
    {
        if(TabuList[i].timeout > 0)
        {
            input = temp;

            pos1 = TabuList[i].pos1;
            pos2 = TabuList[i].pos2;

            std::swap(input[pos1], input[pos2]);

            BazaTabu_input.push_back(input);

            std::unique_ptr<Result> temp_result(new Result(*m_result));
            temp_result->set_result(input);
            temp_result = std::move(inserter->insert(std::move(temp_result)));

            Baza_output.push_back(temp_result->getResult());

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
    column_count = m_result->get_width()/m_result->get_size();

    line_count = m_result->get_height()/m_result->get_size();

    figures_count = column_count*line_count + (column_count*line_count)/2;

    float mnoznik = (float)m_result->get_procent()/100;
    permutation_count = mnoznik*figures_count;
}
