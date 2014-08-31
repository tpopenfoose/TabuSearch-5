#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle();
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(std::vector<std::vector<int>>& p_grid, int p_size, int p_x, int p_y);
};

#endif // RECTANGLE_H
