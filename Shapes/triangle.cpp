#include "triangle.h"

Triangle::Triangle() : Shape(Qt::blue)
{
}

void Triangle::draw(QPainter & p_painter, int p_size, int p_pen_width)
{
    int l_half_pen = p_pen_width/2;
    p_painter.setPen(QPen(m_color));

    int x1=0,x2=0,x3=0,y1=0,y2=0,y3=0;

    x1 = m_x + l_half_pen;
    y1 = m_y + p_size - l_half_pen;

    x2 = m_x + (p_size/2);
    y2 = m_y + l_half_pen;

    x3 = m_x + p_size - l_half_pen;
    y3 = m_y + p_size - l_half_pen;

    p_painter.drawLine(x1+2,y1+2,x2+2,y2+2);
    p_painter.drawLine(x2+2,y2+2,x3+2,y3+2);
    p_painter.drawLine(x1+2,y1+2,x3+2,y3+2);
}

double Triangle::get_area(int p_size)
{
    return 0.5*p_size*p_size;
}

void Triangle::fill_grid(bool** p_grid, int p_size)
{
    for ( int i = m_x; i < m_x+(p_size)/2; i++) {
        for( int j = m_y; j < m_y+p_size; j++) {
            if( prosta1(i, p_size) <= j )
                p_grid[i][j] = 1;
        }
    }

    for ( int i = m_x+(p_size/2); i < m_x+p_size; i++ ) {
        for( int j = m_y; j < m_y+p_size; j++ ) {
            if( prosta2(i, p_size) <= j )
                p_grid[i][j] = 1;
        }
    }
}

double Triangle::prosta1(int p_x, int p_size)
{
    double y=0,y1=0,y2=0,x1=0,x2=0;

    x1 = m_x;
    y1 = m_y + p_size;

    x2 = m_x + (p_size/2);
    y2 = m_y;

    y = (((y2-y1)*(p_x-x1))/(x2-x1))+y1;

    return y;
}

double Triangle::prosta2(int p_x, int p_size)
{
    double y=0,y1=0,y2=0,x1=0,x2=0;

    x1 = m_x + (p_size/2);
    y1 = m_y;

    x2 = m_x + p_size;
    y2 = m_y + p_size;

    y = (((y2-y1)*(p_x-x1))/(x2-x1))+y1;

    return y;
}
