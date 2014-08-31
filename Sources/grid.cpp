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

void Grid::fill_grid(std::vector<std::vector<int>> p_grid, Coordinates p_coordinates)
{
    int p_x = p_coordinates.first;
    int p_y = p_coordinates.second;
    for(unsigned int i = p_x, ii = 0; i < p_x + p_grid.size(); i++, ii++)
    {
        for(unsigned int j = p_y, jj = 0; j < p_y + p_grid.size(); j++, jj++)
        {
            m_grid[i][j] = p_grid[ii][jj];
        }
    }
}
