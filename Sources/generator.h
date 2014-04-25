#ifndef GENERATOR_H
#define GENERATOR_H
#include "shape.h"
#include "rotatableshape.h"
#include "notrotatableshape.h"
#include "globalne.h"

#include <vector>

class Generator
{
public:
    Generator();

    std::vector<Shape> generate(const ConfigData&);
private:
    void calculate_amount(const ConfigData&);
    RotatableShape draw_rotatable_shape();
    NotRotatableShape draw_not_rotatable_shape();

    int m_column_count;
    int m_line_count;
    int m_figures_count;
    int m_permutation_count;
};

#endif // GENERATOR_H
