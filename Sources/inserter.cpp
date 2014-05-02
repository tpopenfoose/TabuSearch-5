
#include "inserter.h"
#include <math.h>
#include <iostream>
#include <memory>

using namespace std;

Grid::Grid(int width, int height)
{
    m_grid = Matrix(height, std::vector<bool>(width,false));
    //std::cout<<"m_grid.size(): "<<m_grid.size()<<std::endl;
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
    delete_grids();
    input.clear();
}

void Inserter::init_insert(void)
{
    current_line = 0;
    current_column = 0;

    insert_stop = false;

    counter = 0;

    new_line = false;
    counter_back = false;
    m_maximal_y = m_result->get_height()-m_result->get_size();
    m_maximal_x = m_result->get_width()-m_result->get_size();

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

void Inserter::delete_grids()
{
    for( int i = 0; i < m_result->get_width(); i++ )
        delete [] grid[i];

    delete [] grid;

    for( int i = 0; i < m_result->get_width(); i++ )
        delete [] f_grid[i];

    delete [] f_grid;
}

std::unique_ptr<Result> Inserter::insert(std::unique_ptr<Result> p_result)
{
    m_result = std::move(p_result);
    init_insert();
    input = m_result->getAll();
    Pair l_coordinates;

    for (counter=0; (counter < input.size()) && (insert_stop == false); counter++)
    {
        l_coordinates = calculate_position(input[counter]);
        if(!counter_back)
            input[counter]->fill_grid(grid,m_result->get_size(), l_coordinates.first, l_coordinates.second);

        counter_back = false;
    }

    //insert_end();
    m_result->set_result(input, counter);
    delete_grids();
    p_result = std::move(m_result);
    return p_result;
}

Pair Inserter::calculate_position(std::shared_ptr<Shape> s)
{
    Pair l_coordinates;
    l_coordinates.first = current_column*m_result->get_size();
    l_coordinates.second = current_line*m_result->get_size();

    calculate_new_f_grid(s, l_coordinates);

    if( shapes_overlines() )
        l_coordinates = fit_overlaping_shape(s, l_coordinates);
    else
        l_coordinates = fit_non_overlaping_shape(s, l_coordinates);

    if( shapes_overlines() ) {
        if(++current_column == column_count) {
            if( ++current_line == line_count ) {
                insert_stop = true;
                return {0,0};
            } else {
                current_column = 0;
                new_line = true;
                counter--;
                counter_back = true;
            }
        } else {
            new_line = true;
            counter--;
            counter_back = true;
        }
    }

    if( !new_line ) {
        if( ++current_column == column_count ) {
            if( ++current_line == line_count ) {
                insert_stop = true;
                return {0,0};
            } else
                current_column = 0;
        }
    }

    new_line = false;

    grid_clear(1);

    return l_coordinates;
}

Pair Inserter::fit_overlaping_shape(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    p_coordinates = fit_overlaping_shape_on_x_and_y(s, p_coordinates);
    p_coordinates = fit_overlaping_shape_on_y(s, p_coordinates);
    p_coordinates = fit_overlaping_shape_on_x(s, p_coordinates);
    return p_coordinates;
}

Pair Inserter::fit_non_overlaping_shape(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    p_coordinates = fit_non_overlaping_shape_on_x_and_y(s, p_coordinates);
    p_coordinates = fit_non_overlaping_shape_on_y(s, p_coordinates);
    p_coordinates = fit_non_overlaping_shape_on_x(s, p_coordinates);
    return p_coordinates;
}

Pair Inserter::fit_overlaping_shape_on_x_and_y(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    Pair mem_coordinates = p_coordinates;

    while( true ) {
        if( not shapes_overlines()&& (p_coordinates.first < m_maximal_x) && (p_coordinates.second < m_maximal_y) ) {
            p_coordinates.first+=1;
            p_coordinates.second+=1;
            calculate_new_f_grid(s, p_coordinates);
        } else {
            if(shapes_overlines() ) {
                p_coordinates.first = mem_coordinates.first;
                p_coordinates.second = mem_coordinates.second;
                calculate_new_f_grid(s, p_coordinates);
            }
            break;
        }
    }

    return p_coordinates;
}

Pair Inserter::fit_overlaping_shape_on_y(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    Pair mem_coordinates = p_coordinates;

    while(true) {
        if( shapes_overlines() && (p_coordinates.second < m_maximal_y) ) {
            p_coordinates.second+=1;
            calculate_new_f_grid(s, p_coordinates);
        } else {
            if( shapes_overlines() ) {
                p_coordinates.second = mem_coordinates.second;
                calculate_new_f_grid(s, p_coordinates);
            }
            break;
        }
    }

    return p_coordinates;
}

Pair Inserter::fit_overlaping_shape_on_x(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    Pair mem_coordinates = p_coordinates;

    while(true) {
        if( shapes_overlines() && (p_coordinates.first < m_maximal_x) ) {
            p_coordinates.first+=1;
            calculate_new_f_grid(s, p_coordinates);
        } else {
            if( shapes_overlines() ) {
                p_coordinates.first = mem_coordinates.first;
                calculate_new_f_grid(s, p_coordinates);
            }
            break;
        }
    }

    return p_coordinates;
}

Pair Inserter::fit_non_overlaping_shape_on_x_and_y(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    while( true ) {
        if( not shapes_overlines() && (p_coordinates.first > 0) && (p_coordinates.second > 0) ) {
            p_coordinates.first-=1;
            p_coordinates.second-=1;
            calculate_new_f_grid(s, p_coordinates);
        } else {
            if( shapes_overlines() ) {
                p_coordinates.first+=1;
                p_coordinates.second+=1;
                calculate_new_f_grid(s, p_coordinates);
                break;
            }

            if( (p_coordinates.first == 0) || (p_coordinates.second == 0))
                break;
        }
    }
    return p_coordinates;
}

Pair Inserter::fit_non_overlaping_shape_on_y(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    while(true) {
        if( not shapes_overlines() && (p_coordinates.second > 0) ) {
            p_coordinates.second-=1;
            calculate_new_f_grid(s, p_coordinates);
        } else {
            if( shapes_overlines() ) {
                p_coordinates.second+=1;
                calculate_new_f_grid(s, p_coordinates);
                break;
            }

            if( p_coordinates.second == 0 )
                break;
        }
    }
    return p_coordinates;
}

Pair Inserter::fit_non_overlaping_shape_on_x(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    while(true) {
        if( not shapes_overlines() && (p_coordinates.first > 0) ) {
            p_coordinates.first-=1;
            calculate_new_f_grid(s, p_coordinates);
        } else {
            if( shapes_overlines() ) {
                p_coordinates.first+=1;
                calculate_new_f_grid(s, p_coordinates);
                break;
            }

            if( p_coordinates.first == 0 )
                break;
        }
    }

    return p_coordinates;
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

void Inserter::calculate_new_f_grid(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    grid_clear(1); //clear f_grid
    s->fill_grid(f_grid, m_result->get_size(), p_coordinates.first, p_coordinates.second);
}

bool Inserter::shapes_overlines(void)
{
    for( int i = 0; i < m_result->get_width(); i++)
    {
        for( int j = 0; j < m_result->get_height(); j++ )
        {
            if( (grid[i][j] == 1) && (f_grid[i][j] == 1) )
                return true;
        }
    }

    return false;
}
