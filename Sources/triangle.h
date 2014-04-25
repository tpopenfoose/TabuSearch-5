#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "rotatableshape.h"

class Triangle : public RotatableShape
{
public:
    Triangle(int p_angle);
    virtual void draw(QPainter &, int, int);
};

#endif // TRIANGLE_H
