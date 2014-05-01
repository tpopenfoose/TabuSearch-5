
#include "inserter.h"
#include <math.h>
#include <iostream>
#include <memory>

using namespace std;

Grid::Grid(int width, int height)
{
    m_grid = Matrix(height, std::vector<bool>(width,false));
    std::cout<<"m_grid.size(): "<<m_grid.size()<<std::endl;
}
bool Grid::operator==(const Grid& p_grid)
{
    return m_grid == p_grid.m_grid ? true : false;
}

Matrix & Grid::data() {
    return m_grid;
}


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

    init_grid();

    grid_clear(0);
    grid_clear(1);
}

void Inserter::init_grid(void)
{
   // test_grid1 = std::unique_ptr<Grid>(new Grid(m_result->get_width(), m_result->get_height()));
   // test_grid2 = std::unique_ptr<Grid>(new Grid(m_result->get_width(), m_result->get_height()));

    grid = new bool *[m_result->get_width()];

    for( int i = 0; i < m_result->get_width(); i++ )
        grid[i] = new bool[m_result->get_height()];

    grid_clear(0);

    f_grid = new bool *[m_result->get_width()];

    for( int i = 0; i < m_result->get_width(); i++ )
        f_grid[i] = new bool[m_result->get_height()];

    grid_clear(1);

   // std::cout<<"m_result->get_width(): "<<m_result->get_width()<<std::endl;
    column_count = m_result->get_width()/m_result->get_size();

    line_count = m_result->get_height()/m_result->get_size();
}

std::unique_ptr<Result> Inserter::insert(std::unique_ptr<Result> p_result)
{
    std::cout<<"insert_1"<<std::endl;
    m_result = std::move(p_result);
    init_insert();
    std::cout<<"insert_2"<<std::endl;
    input = m_result->getAll();

    for (counter=0; (counter < input.size()) && (insert_stop == false); counter++)
    {
        std::cout<<"insert_2_petla_1"<<std::endl;
        calculate_position(input[counter]);
        std::cout<<"insert_2_petla_2"<<std::endl;
        if(!counter_back)
        {
            input[counter]->set_x(pozycja_x);
            input[counter]->set_y(pozycja_y);

            input[counter]->fill_grid(grid,m_result->get_size());
            //input[counter]->fill_grid(test_grid1->data(), m_result->get_size());
        }
        std::cout<<"insert_2_petla_3"<<std::endl;
        counter_back = false;
    }

    //insert_end();
    std::cout<<"insert_3"<<std::endl;
    m_result->set_result(input, counter);

    for( int i = 0; i < m_result->get_width(); i++ )
        delete [] grid[i];

    delete [] grid;

    for( int i = 0; i < m_result->get_width(); i++ )
        delete [] f_grid[i];

    delete [] f_grid;

    p_result = std::move(m_result);
    std::cout<<"insert_4"<<std::endl;
    return p_result;
}

void Inserter::calculate_new_f_grid(std::shared_ptr<Shape> s)
{
    grid_clear(1); //clear f_grid

    s->set_x(pozycja_x);
    s->set_y(pozycja_y);

    //s->fill_grid(test_grid2->data(), m_result->get_size());
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
    //s->fill_grid(test_grid2->data(), m_result->get_size());

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
               /* test_grid2->data()[i][j] = 0;*/ f_grid[i][j] = 0;
            else
              /*  test_grid1->data()[i][j] = 0;*/ grid[i][j] = 0;
        }
    }
}

bool Inserter::compare_grids(void)
{
    //return *test_grid1 == *test_grid2 ? true : false;
   // /*
    for( int i = 0; i < m_result->get_width(); i++)
    {
        for( int j = 0; j < m_result->get_height(); j++ )
        {
            if( (grid[i][j] == 1) && (f_grid[i][j] == 1) )
            //if( (test_grid1->data()[i][j] == 1) && (test_grid2->data()[i][j] == 1) )
                return false;
        }
    }

    return true;
  //  */
}
