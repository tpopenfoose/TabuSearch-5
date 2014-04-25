#ifndef CIRCLE_H
#define CIRCLE_H
#include "notrotatableshape.h"

class Circle : public NotRotatableShape
{
public:
    Circle();
    virtual void draw(QPainter &, int, int);
};

#endif // CIRCLE_H
