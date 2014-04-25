#ifndef SQUARE_H
#define SQUARE_H
#include "notrotatableshape.h"

class Square : public NotRotatableShape
{
public:
    Square();
    virtual void draw(QPainter &, int, int);
};

#endif // SQUARE_H
