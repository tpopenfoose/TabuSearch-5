#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>
#include <QPainter>

class Shape
{
public:
    Shape(QColor);
    virtual void draw(QPainter & painter)=0;
private:
    int m_x;
    int m_y;
    int m_angle;
    QColor m_color;
};

#endif // SHAPE_H
