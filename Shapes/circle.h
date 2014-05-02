#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

class Circle : public Shape
{
public:
    Circle();
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(bool** p_grid, int p_size, int p_x, int p_y);
    //virtual void fill_grid(std::vector<std::vector<bool>>& p_grid, int);
};

#endif // CIRCLE_H
