#include "grid.h"

void Grid::create(int p_width, int p_height)
{
    m_width = p_width;
    m_height = p_height;
    m_grid = new bool *[m_width];

    for( int i = 0; i < m_width; i++ )
        m_grid[i] = new bool[m_height];

    clear();
}

void Grid::deleteAll()
{
    for( int i = 0; i < m_width; i++ )
        delete [] m_grid[i];

    delete [] m_grid;
}

Grid::~Grid()
{
    deleteAll();
}

void Grid::clear()
{
    for ( int i = 0; i < m_width; i++)
    {
        for( int j = 0; j < m_height; j++)
        {
            m_grid[i][j] = 0;
        }
    }
}

bool** Grid::getGrid()
{
    return m_grid;
}

bool Grid::at(int i, int j)
{
    return m_grid[i][j];
}
