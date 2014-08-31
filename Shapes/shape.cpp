#include <shape.h>
#include <sstream>

Shape::Shape(QColor color) :
     m_x(0), m_y(0), m_color(color)
{
}

bool Shape::operator==(const Shape& s) const
{
    return s.m_x == m_x && s.m_y == m_y;
}

bool Shape::operator!=(const Shape& s) const
{
    return s.m_x != m_x || s.m_y != m_y;
}

std::string Shape::value()
{
    std::stringstream ss;
    ss << "x: " << m_x << ", y: " << m_y;
    return ss.str();
}

void Shape::set_x(int p_x)
{
    m_x = p_x;
}

void Shape::set_y(int p_y)
{
    m_y = p_y;
}

Matrix Shape::grid(int p_size)
{
    std::vector<int> zeroes(p_size, 0);
    Matrix grid(p_size, zeroes);
    fill_grid(grid, p_size);
    return grid;
}

void Shape::setCoordinates(Coordinates p_coordinates)
{
    m_x = p_coordinates.first;
    m_y = p_coordinates.second;
}
