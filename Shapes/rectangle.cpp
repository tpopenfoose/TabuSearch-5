#include "rectangle.h"

Rectangle::Rectangle(int p_angle) : RotatableShape(Qt::yellow, p_angle)
{
}

void Rectangle::draw(QPainter & p_painter, int p_size, int p_pen_width)
{
    int l_size = p_size - p_pen_width;
    p_painter.setPen(QPen(m_color));

    if(m_angle%2 == 0 )
        p_painter.drawRect(m_x+2, m_y+2, l_size, l_size - 10);

    else
        p_painter.drawRect(m_x+2, m_y+2, l_size - 10, l_size);
}
