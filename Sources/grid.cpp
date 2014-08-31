#include "grid.h"
#include <iostream>

void Grid::create(int p_width, int p_height)
{
    m_width = p_width;
    m_height = p_height;

    clear();
}

void Grid::deleteAll()
{
    m_grid.clear();
}

Grid::~Grid()
{
    deleteAll();
}

void Grid::clear()
{
    std::vector<int> zeros(m_height, 0);
    m_grid = Matrix(m_width, zeros);
}

Matrix& Grid::getGrid()
{
    return m_grid;
}

bool Grid::at(int i, int j)
{
    return m_grid[i][j];
}
