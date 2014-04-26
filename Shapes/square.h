#ifndef SQUARE_H
#define SQUARE_H
#include "notrotatableshape.h"

class Square : public NotRotatableShape
{
public:
    Square();
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(bool**, int);
};

#endif // SQUARE_H
