#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "rotatableshape.h"

class Triangle : public RotatableShape
{
public:
    Triangle(int p_angle);
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(bool**, int);
private:
    double prosta1(int, int);
    double prosta2(int, int);
};

#endif // TRIANGLE_H
