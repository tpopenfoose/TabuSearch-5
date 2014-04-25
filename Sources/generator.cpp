#include "generator.h"
#include "square.h"
#include "triangle.h"
#include "rectangle.h"
#include "circle.h"
#include <QTime>

Generator::Generator()
{
}

std::vector<Shape> Generator::generate(const ConfigData& p_data)
{
    qsrand((uint)QTime::currentTime().msec());

    calculate_amount(p_data);
    std::vector<Shape> vector;

    for(int i = 0; i < m_figures_count; i++) {
        switch(qrand() % 2)
        {
            case 0: {
                vector.push_back(draw_rotatable_shape());
            } break;

            case 1: {
                vector.push_back(draw_not_rotatable_shape());
            } break;
        }
    }

    return vector;
}

RotatableShape Generator::draw_rotatable_shape()
{
    switch(qrand() % 2)
    {
        case 0: {
            return Triangle(0);
        } break;

        case 1: {
            return Rectangle(0);
        } break;
    }
}

NotRotatableShape Generator::draw_not_rotatable_shape()
{
    switch(qrand() % 2)
    {
        case 0: {
            return Circle();
        } break;

        case 1: {
            return Square();
        } break;
    }
}

void Generator::calculate_amount(const ConfigData& p_data)
{
    m_column_count = p_data.width/p_data.size;

    m_line_count = p_data.height/p_data.size;

    m_figures_count = m_column_count * m_line_count + (m_column_count*m_line_count)/2;

    float mnoznik = (float)p_data.procent/100;
    m_permutation_count = mnoznik*m_figures_count;
}


