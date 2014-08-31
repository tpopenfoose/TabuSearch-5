#pragma once
#include <IGrid.h>

class Grid : public IGrid
{
public:
    Grid() = default;
    virtual void create(int p_width, int p_height);
    virtual void deleteAll();
    virtual void clear();
    virtual Matrix& getGrid();
    virtual bool at(int i, int j);
    virtual void fill_grid(std::vector<std::vector<int>> p_grid, Coordinates p_coordinates);

    virtual ~Grid();

private:
    int m_width;
    int m_height;
    Matrix m_grid;
};
