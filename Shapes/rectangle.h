#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle();
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(bool**, int);
    //virtual void fill_grid(std::vector<std::vector<bool>>& p_grid, int);
};

#endif // RECTANGLE_H
