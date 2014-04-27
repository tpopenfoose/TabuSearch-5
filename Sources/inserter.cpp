
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
    for( int i = 0; i < data.width; i++ )
        delete [] grid[i];

    delete [] grid;

    for( int i = 0; i < data.width; i++ )
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
    grid = new bool *[data.width];

    for( int i = 0; i < data.width; i++ )
        grid[i] = new bool[data.height];

    grid_clear(0);

    f_grid = new bool *[data.width];

    for( int i = 0; i < data.width; i++ )
        f_grid[i] = new bool[data.height];

    grid_clear(1);

    column_count = data.width/data.size;

    line_count = data.height/data.size;
}

TSF Inserter::insert(TSF tsf)
{
    data = tsf.data;

    init_insert();

    input = tsf.all;

    for (counter=0; (counter < input.size()) && (insert_stop == false); counter++)
    {
        calculate_position(input[counter]);

        if(!counter_back)
        {
            input[counter]->set_x(pozycja_x);
            input[counter]->set_y(pozycja_y);

            input[counter]->fill_grid(grid,tsf.data.size);

            output.push_back(input[counter]);
        }
        counter_back = false;
    }

    //insert_end();

    tsf.result = output;
    auto first = tsf.all.begin() + tsf.result.size();
    auto last = tsf.all.end();
    std::vector<std::shared_ptr<Shape>> test(first, last);
    tsf.rest = test;
    //tsf.rest = auto(first, last);

    for( int i = 0; i < data.width; i++ )
        delete [] grid[i];

    delete [] grid;

    for( int i = 0; i < data.width; i++ )
        delete [] f_grid[i];

    delete [] f_grid;

    return tsf;
}

void Inserter::calculate_new_f_grid(std::shared_ptr<Shape> s)
{
    grid_clear(1); //clear f_grid

    s->set_x(pozycja_x);
    s->set_y(pozycja_y);

    s->fill_grid(f_grid, data.size);
}

void Inserter::calculate_position(std::shared_ptr<Shape> s)
{
    grid_clear(1);

    pozycja_x = current_column*data.size;
    pozycja_y = current_line*data.size;

    s->set_x(pozycja_x);
    s->set_y(pozycja_y);

    s->fill_grid(f_grid, data.size);

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
                if( !compare_grids()&& (pozycja_x < (data.width-data.size)) && (pozycja_y < (data.height-data.size)) )
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
                if( !compare_grids() && (pozycja_y < (data.height-data.size)) )
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
                if( !compare_grids() && (pozycja_x < (data.width-data.size)) )
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
    for ( int i = 0; i < data.width; i++)
    {
        for( int j = 0; j < data.height; j++)
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
    for( int i = 0; i < data.width; i++)
    {
        for( int j = 0; j < data.height; j++ )
        {
            if( (grid[i][j] == 1) && (f_grid[i][j] == 1) )
                return false;
        }
    }

    return true;
}

/*
void Inserter::insert_end(void)
{
    bool inserted = false;

    bool brake_signal = false;

    int add_y = 0,add_x = 0;

    int step = 5;

    int i,j;
    int start = (current_line-1)*data.size;

    while(true)
    {
        if( input[counter].figureName == prostokat )
        {
            if( input[counter].pozycja%2 == 0)
            {
                add_x = 0;
                add_y = 10;
            }
            else
            {
                add_x = 10;
                add_y = 0;
            }
        }
        else
        {
            add_x = 0;
            add_y = 0;
        }

        for(i=start; i < (data.height-(data.size-add_y));i+=step)
        {
            for( j = 0; j < (data.width-(data.size-add_x));j+=step)
            {
                input[counter].x = j;
                input[counter].y = i;

                fill_f_grid(input[counter]);

                if(compare_grids())
                {
                    inserted = true;
                    fill_grid(input[counter]);
                    output.push_back(input[counter]);
                    counter++;
                    brake_signal = true;
                    break;
                }

                grid_clear(1);
            }

            if(brake_signal)
            {
                brake_signal = false;
                break;
            }
        }

        if(inserted)
            inserted = false;
        else
            break;
    }

    inserted = false;

    brake_signal = false;

    add_y = 0;
    add_x = 0;

    start = (current_column-1)*data.size;

    while(true)
    {
        if( input[counter].figureName == prostokat )
        {
            if( input[counter].pozycja%2 == 0)
            {
                add_x = 0;
                add_y = 10;
            }
            else
            {
                add_x = 10;
                add_y = 0;
            }
        }
        else
        {
            add_x = 0;
            add_y = 0;
        }

        for(i=start; i < (data.width-(data.size-add_x));i+=step)
        {
            for( j = 0; j < (data.height-(data.size-add_y));j+=step)
            {
                input[counter].x = i;
                input[counter].y = j;

                fill_f_grid(input[counter]);

                if(compare_grids())
                {
                    inserted = true;
                    fill_grid(input[counter]);
                    output.push_back(input[counter]);
                    counter++;
                    brake_signal = true;
                    break;
                }

                grid_clear(1);
            }

            if(brake_signal)
            {
                brake_signal = false;
                break;
            }
        }

        if(inserted)
            inserted = false;
        else
            break;
    }
}
*/
