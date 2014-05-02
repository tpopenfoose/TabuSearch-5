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
double Circle::get_area(int p_size)
{
    return 3.14*(p_size/2)*(p_size/2);
}

//void Circle::fill_grid(std::vector<std::vector<bool> > &p_grid, int p_size)
void Circle::fill_grid(bool** p_grid, int p_size, int p_x, int p_y)
{
    m_x = p_x;
    m_y = p_y;
    for (int i = m_x;i<m_x+p_size;i++)
    {
        for(int j = m_y;j<m_y+p_size;j++)
        {
            int od = sqrt( pow(j-(m_y+(p_size/2)),2) + pow(i-(m_x+(p_size/2)),2) );

            if( od <= (p_size/2) )
                p_grid[i][j] = 1;

        }
    }
}

