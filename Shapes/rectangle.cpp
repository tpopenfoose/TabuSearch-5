#include "rectangle.h"

Rectangle::Rectangle() : Shape(Qt::yellow)
{
}

void Rectangle::draw(QPainter & p_painter, int p_size, int p_pen_width)
{
    int l_size = p_size - p_pen_width;
    QPen pen;
    pen.setColor(m_color);
    pen.setWidth(p_pen_width);
    p_painter.setPen(pen);

    p_painter.drawRect(m_x+2, m_y+2, l_size, l_size - 10);
}

double Rectangle::get_area(int p_size)
{
    return p_size*p_size*0.66;
}

void Rectangle::fill_grid(bool** p_grid, int p_size)
{
    for (int i = m_x;i<m_x+p_size;i++) {
        for(int j = m_y;j<m_y+(p_size-10);j++)
            p_grid[i][j] = 1;
    }
}
