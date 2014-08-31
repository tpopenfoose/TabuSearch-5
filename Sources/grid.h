#pragma once
#include <IGrid.h>

class Grid : public IGrid
{
public:
    Grid() = default;
    virtual void create(int p_width, int p_height);
    virtual void deleteAll();
    virtual void clear();
    virtual bool** getGrid();
    virtual bool at(int i, int j);

    virtual ~Grid();

private:
    int m_width;
    int m_height;
    bool** m_grid;
};
