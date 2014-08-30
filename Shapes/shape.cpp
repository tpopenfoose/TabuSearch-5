#include "shape.h"

Shape::Shape(QColor color) :
     m_x(0), m_y(0), m_color(color)
{
}

bool Shape::operator==(const Shape& s) const
{
    return s.m_x == m_x && s.m_y == m_y;
}

void Shape::set_x(int p_x)
{
    m_x = p_x;
}

void Shape::set_y(int p_y)
{
    m_y = p_y;
}
