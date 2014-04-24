
#include "inserter.h"
#include <math.h>
#include <iostream>

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
            input[counter].x = pozycja_x;
            input[counter].y = pozycja_y;

            fill_grid(input[counter]);

            output.push_back(input[counter]);
        }
        counter_back = false;
    }

    insert_end();

    tsf.result = output;

    tsf.rest = tsf.all.mid(tsf.result.size());

    for( int i = 0; i < data.width; i++ )
        delete [] grid[i];

    delete [] grid;

    for( int i = 0; i < data.width; i++ )
        delete [] f_grid[i];

    delete [] f_grid;

    return tsf;
}

void Inserter::calculate_new_f_grid(Figure f)
{
    grid_clear(1); //clear f_grid

    f.x = pozycja_x;
    f.y = pozycja_y;

    fill_f_grid(f);
}

void Inserter::fill_f_grid(Figure f)
{
    switch(f.figureName)
    {
        case kwadrat:
            fill_square(f,1);
        break;

        case kolo:
            fill_elipse(f,1);
        break;

        case trojkat:
            fill_triangle(f,1);
        break;

        case prostokat:
            fill_rectangle(f,1);
        break;
    }
}

void Inserter::calculate_position(Figure f)
{
    grid_clear(1);

    pozycja_x = current_column*data.size;
    pozycja_y = current_line*data.size;

    f.x = pozycja_x;
    f.y = pozycja_y;

    fill_f_grid(f);

    if( compare_grids() )
    {
            while( true )
            {
                if( compare_grids()&& (pozycja_x > 0) && (pozycja_y > 0) )
                {
                    pozycja_x-=1;
                    pozycja_y-=1;
                    calculate_new_f_grid(f);
                }

                else
                {
                    if( !compare_grids() )
                    {
                        pozycja_x+=1;
                        pozycja_y+=1;
                        calculate_new_f_grid(f);
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
                    calculate_new_f_grid(f);
                }

                else
                {
                    if( !compare_grids() )
                    {
                        pozycja_y+=1;
                        calculate_new_f_grid(f);
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
                    calculate_new_f_grid(f);
                }

                else
                {
                    if( !compare_grids() )
                    {
                        pozycja_x+=1;
                        calculate_new_f_grid(f);
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
                    calculate_new_f_grid(f);
                }

                else
                {
                    if( compare_grids() )
                        break;
                    else
                    {
                        pozycja_x = pozycja_x_mem;
                        pozycja_y = pozycja_y_mem;
                        calculate_new_f_grid(f);
                        break;
                    }
                }
            }

            while(true)
            {
                if( !compare_grids() && (pozycja_y < (data.height-data.size)) )
                {
                    pozycja_y+=1;
                    calculate_new_f_grid(f);
                }

                else
                {
                    if( compare_grids() )
                        break;
                    else
                    {
                        pozycja_y = pozycja_y_mem;
                        calculate_new_f_grid(f);
                        break;
                    }
                }
            }

            while(true)
            {
                if( !compare_grids() && (pozycja_x < (data.width-data.size)) )
                {
                    pozycja_x+=1;
                    calculate_new_f_grid(f);
                }

                else
                {
                    if( compare_grids() )
                        break;
                    else
                    {
                        pozycja_x = pozycja_x_mem;
                        calculate_new_f_grid(f);
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

void Inserter::fill_grid(Figure f)
{
    switch(f.figureName)
    {
        case kolo:
            fill_elipse(f,0);
        break;

        case kwadrat:
            fill_square(f,0);
        break;

        case prostokat:
            fill_rectangle(f,0);
        break;

        case trojkat:
            fill_triangle(f,0);
        break;
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

void Inserter::fill_square(Figure f, bool gn)
{
    for (int i = f.x;i<f.x+data.size;i++)
    {
        for(int j = f.y;j<f.y+data.size;j++)
        {
            if(gn)
                f_grid[i][j] = 1;
            else
                grid[i][j] = 1;
        }
    }
}

void Inserter::fill_elipse(Figure f, bool gn)
{
    for (int i = f.x;i<f.x+data.size;i++)
    {
        for(int j = f.y;j<f.y+data.size;j++)
        {
            int od = sqrt( pow(j-(f.y+(data.size/2)),2) + pow(i-(f.x+(data.size/2)),2) );

            if( od <= (data.size/2) )
            {
                if(gn)
                    f_grid[i][j] = 1;
                else
                    grid[i][j] = 1;
            }
        }
    }
}

void Inserter::fill_rectangle(Figure f, bool gn)
{
    if(f.pozycja%2 == 0 )
    {
        for (int i = f.x;i<f.x+data.size;i++)
        {
            for(int j = f.y;j<f.y+(data.size-10);j++)
            {
                if(gn)
                    f_grid[i][j] = 1;
                else
                    grid[i][j] = 1;
            }
        }
    }

    else
    {
        for (int i = f.x;i<f.x+(data.size-10);i++)
        {
            for(int j = f.y;j<f.y+data.size;j++)
            {
                if(gn)
                    f_grid[i][j] = 1;
                else
                    grid[i][j] = 1;
            }
        }
    }
}

void Inserter::fill_triangle(Figure f,bool gn)
{
    if(f.pozycja == 0 )
    {
        for ( int i = f.x; i < f.x+(data.size)/2; i++)
        {
            for( int j = f.y; j < f.y+data.size; j++)
            {
                if( prosta1(f,i) <= j )
                {
                    if(gn)
                        f_grid[i][j] = 1;
                    else
                        grid[i][j] = 1;
                }
            }
        }

        for ( int i = f.x+(data.size/2); i < f.x+data.size; i++ )
        {
            for( int j = f.y; j < f.y+data.size; j++ )
            {
                if( prosta2(f,i) <= j )
                {
                    if(gn)
                        f_grid[i][j] = 1;
                    else
                        grid[i][j] = 1;
                }
            }
        }
    }

    if(f.pozycja == 1 )
    {
        for ( int i = f.x; i < f.x+data.size; i++)
        {
            for( int j = f.y; j < f.y+(data.size/2); j++)
            {
                if( prosta1(f,i) <= j )
                {
                    if(gn)
                        f_grid[i][j] = 1;
                    else
                        grid[i][j] = 1;
                }
            }
        }

        for ( int i = f.x; i < f.x+data.size; i++ )
        {
            for( int j = f.y+(data.size/2); j < f.y+data.size; j++ )
            {
                if( prosta2(f,i) >= j )
                {
                    if(gn)
                        f_grid[i][j] = 1;
                    else
                        grid[i][j] = 1;
                }
            }
        }
    }

    if(f.pozycja == 2 )
    {
        for ( int i = f.x; i < f.x+(data.size)/2; i++)
        {
            for( int j = f.y; j < f.y+data.size; j++)
            {
                if( prosta1(f,i) >= j )
                {
                    if(gn)
                        f_grid[i][j] = 1;
                    else
                        grid[i][j] = 1;
                }
            }
        }

        for ( int i = f.x+(data.size/2); i < f.x+data.size; i++ )
        {
            for( int j = f.y; j < f.y+data.size; j++ )
            {
                if( prosta2(f,i) >= j )
                {
                    if(gn)
                        f_grid[i][j] = 1;
                    else
                        grid[i][j] = 1;
                }
            }
        }
    }

    if(f.pozycja == 3 )
    {
        for ( int i = f.x; i < f.x+data.size; i++)
        {
            for( int j = f.y; j < f.y+(data.size/2); j++)
            {
                if( prosta1(f,i) <= j )
                {
                    if(gn)
                        f_grid[i][j] = 1;
                    else
                        grid[i][j] = 1;
                }
            }
        }

        for ( int i = f.x; i < f.x+data.size; i++ )
        {
            for( int j = f.y+(data.size/2); j < f.y+data.size; j++ )
            {
                if( prosta2(f,i) >= j )
                {
                    if(gn)
                        f_grid[i][j] = 1;
                    else
                        grid[i][j] = 1;
                }
            }
        }
    }
}

double Inserter::prosta1(Figure f,int x)
{
    double y=0,y1=0,y2=0,x1=0,x2=0;

    switch(f.pozycja)
    {
        case 0:
            x1 = f.x;
            y1 = f.y + data.size;

            x2 = f.x + (data.size/2);
            y2 = f.y;
        break;

        case 1:
            x1 = f.x;
            y1 = f.y;

            x2 = f.x + data.size;
            y2 = f.y + (data.size/2);
        break;

        case 2:
            x1 = f.x;
            y1 = f.y;

            x2 = f.x + (data.size/2);
            y2 = f.y + data.size;
        break;

        case 3:
            x1 = f.x + data.size;
            y1 = f.y;

            x2 = f.x;
            y2 = f.y + (data.size/2);
        break;
    }

    y = (((y2-y1)*(x-x1))/(x2-x1))+y1;

    return y;
}

double Inserter::prosta2(Figure f,int x)
{
    double y=0,y1=0,y2=0,x1=0,x2=0;

    switch(f.pozycja)
    {
        case 0:
            x1 = f.x + (data.size/2);
            y1 = f.y;

            x2 = f.x + data.size;
            y2 = f.y + data.size;
        break;

        case 1:
            x1 = f.x + data.size;
            y1 = f.y + (data.size/2);

            x2 = f.x;
            y2 = f.y + data.size;
        break;

        case 2:
            x1 = f.x + (data.size/2);
            y1 = f.y + data.size;

            x2 = f.x + data.size;
            y2 = f.y;
        break;

        case 3:
            x1 = f.x;
            y1 = f.y + (data.size/2);

            x2 = f.x + data.size;
            y2 = f.y + data.size;
        break;
    }

    y = (((y2-y1)*(x-x1))/(x2-x1))+y1;

    return y;
}

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
