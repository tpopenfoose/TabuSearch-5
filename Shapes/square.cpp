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

double Square::get_area(int p_size)
{
    return p_size*p_size;
}

void Square::fill_grid(bool** p_grid, int p_size)
{
    for (int i = m_x;i<m_x+p_size;i++) {
        for(int j = m_y;j<m_y+p_size;j++)
            p_grid[i][j] = 1;
    }
}
