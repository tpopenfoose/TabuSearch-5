#ifndef SQUARE_H
#define SQUARE_H
#include "shape.h"

class Square : public Shape
{
public:
    Square();
    virtual void draw(QPainter &, int, int);
};

#endif // SQUARE_H
