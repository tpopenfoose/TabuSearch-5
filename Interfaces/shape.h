#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>
#include <QPainter>

class Shape
{
public:
    Shape(QColor);
    virtual void draw(QPainter & p_painter, int p_size, int p_pen_width);
protected:
    int m_x;
    int m_y;
    QColor m_color;
};

#endif // SHAPE_H
