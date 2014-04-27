#include "generator.h"
#include "square.h"
#include "triangle.h"
#include "rectangle.h"
#include "circle.h"
#include <QTime>
#include <memory>

Generator::Generator()
{
}

std::vector<std::shared_ptr<Shape>> Generator::generate(const ConfigData& p_data)
{
    qsrand((uint)QTime::currentTime().msec());

    calculate_amount(p_data);
    std::vector<std::shared_ptr<Shape>> vector;

    for(int i = 0; i < m_figures_count; i++) {
        switch(qrand() % 4)
        {
            case 0: {
                vector.push_back(std::shared_ptr<Shape>(new Triangle()));
            } break;

            case 1: {
                vector.push_back(std::shared_ptr<Shape>(new Rectangle()));
            } break;

            case 2: {
                vector.push_back(std::shared_ptr<Shape>(new Circle()));
            } break;

            case 3: {
                vector.push_back(std::shared_ptr<Shape>(new Square()));
            } break;
        }
    }

    return vector;
}

void Generator::calculate_amount(const ConfigData& p_data)
{
    m_column_count = p_data.width/p_data.size;

    m_line_count = p_data.height/p_data.size;

    m_figures_count = m_column_count * m_line_count + (m_column_count*m_line_count)/2;

    float mnoznik = (float)p_data.procent/100;
    m_permutation_count = mnoznik*m_figures_count;
}
