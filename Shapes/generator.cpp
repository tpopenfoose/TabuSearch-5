#include "generator.h"
#include "square.h"
#include "triangle.h"
#include "rectangle.h"
#include "circle.h"
#include <QTime>
#include <memory>
#include <iostream>

Generator::Generator()
{
}

std::vector<std::shared_ptr<Shape> > Generator::generate(const ConfigData& p_data)
{
    int l_shapes_count = calculate_shapes_count(p_data);

    return generate_vector(l_shapes_count);
}

std::vector<std::shared_ptr<Shape> > Generator::generate_vector(int p_shapes_count)
{
    qsrand((uint)QTime::currentTime().msec());
    std::vector<std::shared_ptr<Shape>> vector;

    for(int i = 0; i < p_shapes_count; i++) {
        switch(qrand() % 4)
        {
            case 0: {
                vector.emplace_back(std::make_shared<Triangle>());
            } break;

            case 1: {
                vector.emplace_back(std::make_shared<Rectangle>());
            } break;

            case 2: {
                vector.emplace_back(std::make_shared<Circle>());
            } break;

            case 3: {
                vector.emplace_back(std::make_shared<Square>());
            } break;
        }
    }

    return vector;
}

int Generator::calculate_shapes_count(const ConfigData& p_data)
{
    int l_column_count = calculate_column_count(p_data.width, p_data.size);
    int l_line_count = calculate_line_count(p_data.height, p_data.size);

    return l_column_count * l_line_count + (l_column_count*l_line_count)/2;
}

int Generator::calculate_column_count(int p_width, int p_size)
{
    return p_width/p_size;
}

int Generator::calculate_line_count(int p_height, int p_size)
{
    return p_height/p_size;
}
