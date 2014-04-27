#ifndef GENERATOR_H
#define GENERATOR_H
#include "shape.h"
#include "globalne.h"

#include <vector>

class Generator
{
public:
    Generator();

    std::vector<std::shared_ptr<Shape>> generate(const ConfigData&);
private:
    void calculate_amount(const ConfigData&);

    int m_column_count;
    int m_line_count;
    int m_figures_count;
    int m_permutation_count;
};

#endif // GENERATOR_H
