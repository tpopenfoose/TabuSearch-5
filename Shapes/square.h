#ifndef SQUARE_H
#define SQUARE_H
#include "shape.h"

class Square : public Shape
{
public:
    Square();
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(std::vector<std::vector<int>>& p_grid, int p_size, int p_x, int p_y);
};

#endif // SQUARE_H
