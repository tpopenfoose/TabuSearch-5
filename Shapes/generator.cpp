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

std::unique_ptr<Result> Generator::generate(std::unique_ptr<Result> p_result)
{
    p_result = std::move(calculate_shapes_count(std::move(p_result)));
    p_result->set_all(generate_vector());

    return p_result;
}

std::vector<std::shared_ptr<Shape> > Generator::generate_vector()
{
    qsrand((uint)QTime::currentTime().msec());
    std::vector<std::shared_ptr<Shape>> vector;

    for(int i = 0; i < m_shapes_count; i++) {
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

std::unique_ptr<Result> Generator::calculate_shapes_count(std::unique_ptr<Result> p_result)
{
    int l_column_count = calculate_column_count(p_result->get_width(), p_result->get_size());
    int l_line_count = calculate_line_count(p_result->get_height(), p_result->get_size());

    m_shapes_count = l_column_count * l_line_count + (l_column_count*l_line_count)/2;
    return p_result;
}

int Generator::calculate_column_count(int p_width, int p_size)
{
    return p_width/p_size;
}

int Generator::calculate_line_count(int p_height, int p_size)
{
    return p_height/p_size;
}
