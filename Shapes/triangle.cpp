#include "triangle.h"

Triangle::Triangle(int p_angle) : RotatableShape(Qt::blue, p_angle)
{
}

void Triangle::draw(QPainter & p_painter, int p_size, int p_pen_width)
{
    int l_half_pen = p_pen_width/2;
    p_painter.setPen(QPen(m_color));

    int x1=0,x2=0,x3=0,y1=0,y2=0,y3=0;

    if( m_angle == 0)
    {
        x1 = m_x + l_half_pen;
        y1 = m_y + p_size - l_half_pen;

        x2 = m_x + (p_size/2);
        y2 = m_y + l_half_pen;

        x3 = m_x + p_size - l_half_pen;
        y3 = m_y + p_size - l_half_pen;
    }

    if( m_angle == 1)
    {
        x1 = m_x + l_half_pen;
        y1 = m_y + l_half_pen;

        x2 = m_x + p_size - l_half_pen;
        y2 = m_y + (p_size/2);

        x3 = m_x + l_half_pen;
        y3 = m_y + p_size - l_half_pen;

    }
    if( m_angle == 2)
    {
        x1 = m_x + l_half_pen;
        y1 = m_y + l_half_pen;

        x2 = m_x + (p_size/2);
        y2 = m_y + p_size - l_half_pen;

        x3 = m_x + p_size - l_half_pen;
        y3 = m_y + l_half_pen;

    }
    if( m_angle == 3)
    {
        x1 = m_x + p_size - l_half_pen;
        y1 = m_y + l_half_pen;

        x2 = m_x + l_half_pen;
        y2 = m_y + (p_size/2);

        x3 = m_x + p_size - l_half_pen;
        y3 = m_y + p_size - l_half_pen;
    }

    p_painter.drawLine(x1+2,y1+2,x2+2,y2+2);
    p_painter.drawLine(x2+2,y2+2,x3+2,y3+2);
    p_painter.drawLine(x1+2,y1+2,x3+2,y3+2);
}
