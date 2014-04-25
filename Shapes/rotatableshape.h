#ifndef ROTATABLESHAPE_H
#define ROTATABLESHAPE_H
#include "shape.h"

class RotatableShape : public Shape
{
public:
    RotatableShape(QColor, int);
protected:
    int m_angle;
};

#endif // ROTATABLESHAPE_H
