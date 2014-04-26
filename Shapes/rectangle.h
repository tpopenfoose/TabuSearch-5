#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "rotatableshape.h"

class Rectangle : public RotatableShape
{
public:
    Rectangle(int p_angle);
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(bool**, int);
};

#endif // RECTANGLE_H
