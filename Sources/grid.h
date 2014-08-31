#pragma once

class Grid
{
public:
    Grid() = default;
    virtual void create(int p_width, int p_height);
    virtual ~Grid();
    virtual void clear();
    virtual bool** getGrid();
    virtual bool at(int i, int j);

private:
    int m_width;
    int m_height;
    bool** m_grid;
};
