#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

class Circle : public Shape
{
public:
    Circle();
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(bool**, int);
    //virtual void fill_grid(std::vector<std::vector<bool>>& p_grid, int);
};

#endif // CIRCLE_H
