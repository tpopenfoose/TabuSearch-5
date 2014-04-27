#include "shape.h"

Shape::Shape()
{

}

Shape::~Shape()
{

}

Shape::Shape(QColor color) :
     m_x(0), m_y(0), m_color(color)
{
}

void Shape::set_x(int p_x)
{
    m_x = p_x;
}

void Shape::set_y(int p_y)
{
    m_y = p_y;
}
