#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>
#include <QPainter>
#include <math.h>

class Shape
{
public:
    Shape();
    Shape(QColor);
    virtual void draw(QPainter & p_painter, int p_size, int p_pen_width)=0;
    virtual double get_area(int)=0;
    virtual void fill_grid(bool**, int)=0;
    void set_x(int);
    void set_y(int);
    virtual ~Shape();
protected:
    int m_x;
    int m_y;
    QColor m_color;
};

#endif // SHAPE_H