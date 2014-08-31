#include <inserter.h>
#include <math.h>
#include <iostream>
#include <memory>
#include <utility>

using namespace std;

Inserter::Inserter(QObject *parent) :
    QObject(parent),
    grid(std::unique_ptr<Grid>(new Grid)),
    f_grid(std::unique_ptr<Grid>(new Grid))
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
    m_maximal_y = m_data.height-m_data.size;
    m_maximal_x = m_data.width-m_data.size;

    init_grid();

    grid->clear();
    f_grid->clear();
}

void Inserter::init_grid(void)
{
    grid->create(m_data.width, m_data.height);
    f_grid->create(m_data.width, m_data.height);

    column_count = m_data.width/m_data.size;
    line_count = m_data.height/m_data.size;
}

void Inserter::delete_grids()
{
    grid.release();
    f_grid.release();
}

Shapes Inserter::insert(std::vector<std::shared_ptr<Shape>> p_shapes, const ConfigData& p_data)
{
    m_data = p_data;
    init_insert();
    input = p_shapes;
    Pair l_coordinates;

    for (counter=0; (counter < input.size()) && !insert_stop; counter++)
    {
        l_coordinates = calculate_position(input[counter]);
        if(!counter_back && !insert_stop)
            input[counter]->fill_grid(grid->getGrid() ,m_data.size, l_coordinates.first, l_coordinates.second);

        counter_back = false;
    }

    //insert_end();
    delete_grids();
    return std::make_pair(input, counter);
}

Pair Inserter::calculate_position(std::shared_ptr<Shape> s)
{
    Pair l_coordinates;
    l_coordinates.first = current_column*m_data.size;
    l_coordinates.second = current_line*m_data.size;

    calculate_new_f_grid(s, l_coordinates);

    if( shapes_overlines() )
        l_coordinates = fit_overlaping_shape(s, l_coordinates);
    else
        l_coordinates = fit_non_overlaping_shape(s, l_coordinates);

    if( shapes_overlines() ) {
        if(++current_column >= column_count) {
            if( ++current_line >= line_count ) {
                insert_stop = true;
                return Pair(-1,-1);
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
        if( ++current_column >= column_count ) {
            if( ++current_line >= line_count ) {
                insert_stop = true;
                return Pair(-1,-1);
            } else
                current_column = 0;
        }
    }

    new_line = false;

    f_grid->clear();

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

void Inserter::calculate_new_f_grid(std::shared_ptr<Shape> s, Pair p_coordinates)
{
    f_grid->clear();
    s->fill_grid(f_grid->getGrid(), m_data.size, p_coordinates.first, p_coordinates.second);
}

bool Inserter::shapes_overlines(void)
{
    for( int i = 0; i < m_data.width; i++)
    {
        for( int j = 0; j < m_data.height; j++ )
        {
            if( (grid->at(i,j) == 1) && (f_grid->at(i,j) == 1) )
                return true;
        }
    }

    return false;
}
