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

double Rectangle::get_area(int p_size)
{
    return p_size*p_size*0.66;
}

void Rectangle::fill_grid(bool** p_grid, int p_size)
{
    if(m_angle%2 == 0 ) {
        for (int i = m_x;i<m_x+p_size;i++) {
            for(int j = m_y;j<m_y+(p_size-10);j++)
                p_grid[i][j] = 1;
        }
    }

    else {
        for (int i = m_x;i<m_x+(p_size-10);i++) {
            for(int j = m_y;j<m_y+p_size;j++)
                    p_grid[i][j] = 1;
        }
    }
}
