#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>
#include <QPainter>
#include <math.h>

class Shape
{
public:
    Shape() = default;
    Shape(QColor);
    bool operator==(const Shape& s) const;
    bool operator!=(const Shape& s) const;
    virtual void draw(QPainter & p_painter, int p_size, int p_pen_width)=0;
    virtual double get_area(int)=0;
    virtual void fill_grid(bool**, int, int, int)=0;
    //virtual void fill_grid(std::vector<std::vector<bool>>& p_grid, int)=0;
    virtual void set_x(int);
    virtual void set_y(int);
    virtual std::string value();
    virtual ~Shape() = default;
protected:
    int m_x;
    int m_y;
    QColor m_color;
};

#endif // SHAPE_H
