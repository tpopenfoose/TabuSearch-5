
#include "inserter.h"
#include <math.h>
#include <iostream>
#include <memory>

using namespace std;

Inserter::Inserter(QObject *parent) :
    QObject(parent)
{
}

Inserter::~Inserter()
{
    for( int i = 0; i < m_result->get_width(); i++ )
        delete [] grid[i];

    delete [] grid;

    for( int i = 0; i < m_result->get_width(); i++ )
        delete [] f_grid[i];

    delete [] f_grid;

    input.clear();
    output.clear();
}

void Inserter::init_insert(void)
{
    pozycja_x = 0;
    pozycja_y = 0;

    current_line = 0;
    current_column = 0;

    insert_stop = false;

    counter = 0;

    new_line = false;
    counter_back = false;

    output.clear();

    init_grid();

    grid_clear(0);
    grid_clear(1);
}

void Inserter::init_grid(void)
{
    grid = new bool *[m_result->get_width()];

    for( int i = 0; i < m_result->get_width(); i++ )
        grid[i] = new bool[m_result->get_height()];

    grid_clear(0);

    f_grid = new bool *[m_result->get_width()];

    for( int i = 0; i < m_result->get_width(); i++ )
        f_grid[i] = new bool[m_result->get_height()];

    grid_clear(1);

    column_count = m_result->get_width()/m_result->get_size();

    line_count = m_result->get_height()/m_result->get_size();
}

std::unique_ptr<Result> Inserter::insert(std::unique_ptr<Result> p_result)
{
    m_result = std::move(p_result);
    init_insert();

    input = m_result->getAll();

    for (counter=0; (counter < input.size()) && (insert_stop == false); counter++)
    {
        calculate_position(input[counter]);

        if(!counter_back)
        {
            input[counter]->set_x(pozycja_x);
            input[counter]->set_y(pozycja_y);

            input[counter]->fill_grid(grid,m_result->get_size());

            output.push_back(input[counter]);
        }
        counter_back = false;
    }

    //insert_end();

    m_result->set_result(output);
    //auto first = tsf.all.begin() + tsf.result.size();
    //auto last = tsf.all.end();
    //std::vector<std::shared_ptr<Shape>> test(first, last);
    //tsf.rest = test;
    //tsf.rest = auto(first, last);

    for( int i = 0; i < m_result->get_width(); i++ )
        delete [] grid[i];

    delete [] grid;

    for( int i = 0; i < m_result->get_width(); i++ )
        delete [] f_grid[i];

    delete [] f_grid;

    p_result = std::move(m_result);
    return p_result;
}

void Inserter::calculate_new_f_grid(std::shared_ptr<Shape> s)
{
    grid_clear(1); //clear f_grid

    s->set_x(pozycja_x);
    s->set_y(pozycja_y);

    s->fill_grid(f_grid, m_result->get_size());
}

void Inserter::calculate_position(std::shared_ptr<Shape> s)
{
    grid_clear(1);

    pozycja_x = current_column*m_result->get_size();
    pozycja_y = current_line*m_result->get_size();

    s->set_x(pozycja_x);
    s->set_y(pozycja_y);

    s->fill_grid(f_grid, m_result->get_size());

    if( compare_grids() )
    {
            while( true )
            {
                if( compare_grids()&& (pozycja_x > 0) && (pozycja_y > 0) )
                {
                    pozycja_x-=1;
                    pozycja_y-=1;
                    calculate_new_f_grid(s);
                }

                else
                {
                    if( !compare_grids() )
                    {
                        pozycja_x+=1;
                        pozycja_y+=1;
                        calculate_new_f_grid(s);
                        break;
                    }

                    if( (pozycja_x == 0) || (pozycja_y == 0))
                        break;
                }
            }

            while(true)
            {
                if( compare_grids() && (pozycja_y > 0) )
                {
                    pozycja_y-=1;
                    calculate_new_f_grid(s);
                }

                else
                {
                    if( !compare_grids() )
                    {
                        pozycja_y+=1;
                        calculate_new_f_grid(s);
                        break;
                    }

                    if( pozycja_y == 0 )
                        break;
                }
            }

            while(true)
            {
                if( compare_grids() && (pozycja_x > 0) )
                {
                    pozycja_x-=1;
                    calculate_new_f_grid(s);
                }

                else
                {
                    if( !compare_grids() )
                    {
                        pozycja_x+=1;
                        calculate_new_f_grid(s);
                        break;
                    }

                    if( pozycja_x == 0 )
                        break;
                }
            }
        }

        else
        {
            int pozycja_x_mem = pozycja_x;
            int pozycja_y_mem = pozycja_y;

            while( true )
            {
                if( !compare_grids()&& (pozycja_x < (m_result->get_width()-m_result->get_size())) && (pozycja_y < (m_result->get_height()-m_result->get_size())) )
                {
                    pozycja_x+=1;
                    pozycja_y+=1;
                    calculate_new_f_grid(s);
                }

                else
                {
                    if( compare_grids() )
                        break;
                    else
                    {
                        pozycja_x = pozycja_x_mem;
                        pozycja_y = pozycja_y_mem;
                        calculate_new_f_grid(s);
                        break;
                    }
                }
            }

            while(true)
            {
                if( !compare_grids() && (pozycja_y < (m_result->get_height()-m_result->get_size())) )
                {
                    pozycja_y+=1;
                    calculate_new_f_grid(s);
                }

                else
                {
                    if( compare_grids() )
                        break;
                    else
                    {
                        pozycja_y = pozycja_y_mem;
                        calculate_new_f_grid(s);
                        break;
                    }
                }
            }

            while(true)
            {
                if( !compare_grids() && (pozycja_x < (m_result->get_width()-m_result->get_size())) )
                {
                    pozycja_x+=1;
                    calculate_new_f_grid(s);
                }

                else
                {
                    if( compare_grids() )
                        break;
                    else
                    {
                        pozycja_x = pozycja_x_mem;
                        calculate_new_f_grid(s);
                        break;
                    }
                }
            }
        }

        if( !compare_grids() )
        {
            if(++current_column == column_count)
            {
                if( ++current_line == line_count )
                {
                    insert_stop = true;
                    return;
                }

                else
                {
                    current_column = 0;
                    new_line = true;
                    counter--;
                    counter_back = true;
                }
            }

            else
            {
                new_line = true;
                counter--;
                counter_back = true;
            }
        }

        if( !new_line )
        {
            if( ++current_column == column_count )
            {
                if( ++current_line == line_count )
                {
                    insert_stop = true;
                    return;
                }
                else
                    current_column = 0;
            }
        }

        new_line = false;

    grid_clear(1);
}

void Inserter::grid_clear(bool gn)
{
    for ( int i = 0; i < m_result->get_width(); i++)
    {
        for( int j = 0; j < m_result->get_height(); j++)
        {
            if(gn)
                f_grid[i][j] = 0;
            else
                grid[i][j] = 0;
        }
    }
}

bool Inserter::compare_grids(void)
{
    for( int i = 0; i < m_result->get_width(); i++)
    {
        for( int j = 0; j < m_result->get_height(); j++ )
        {
            if( (grid[i][j] == 1) && (f_grid[i][j] == 1) )
                return false;
        }
    }

    return true;
}
