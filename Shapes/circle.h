#ifndef CIRCLE_H
#define CIRCLE_H
#include "notrotatableshape.h"

class Circle : public NotRotatableShape
{
public:
    Circle();
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(bool**, int);
};

#endif // CIRCLE_H
