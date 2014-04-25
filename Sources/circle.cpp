#include "circle.h"
#include <QPen>

Circle::Circle() : Shape(Qt::red)
{
}

void Circle::draw(QPainter & p_painter, int p_size, int p_pen_width)
{
    int l_size = p_size - p_pen_width;
    p_painter.setPen(QPen(m_color));
    p_painter.drawEllipse(m_x+2, m_y+2, l_size, l_size);
}

