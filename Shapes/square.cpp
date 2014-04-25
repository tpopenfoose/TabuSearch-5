#include "square.h"
#include <QPen>

Square::Square() : NotRotatableShape(Qt::green)
{
}

void Square::draw(QPainter & p_painter, int p_size, int p_pen_width)
{
    int l_size = p_size - p_pen_width;
    p_painter.setPen(QPen(m_color));
    p_painter.drawRect(m_x+2, m_y+2, l_size, l_size);
}
