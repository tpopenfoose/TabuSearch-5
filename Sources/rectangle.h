#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "rotatableshape.h"

class Rectangle : public RotatableShape
{
public:
    Rectangle(int p_angle);
    virtual void draw(QPainter &, int, int);
};

#endif // RECTANGLE_H
