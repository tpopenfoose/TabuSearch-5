#ifndef GENERATOR_H
#define GENERATOR_H
#include "shape.h"
#include "result.h"
#include <memory>
#include <vector>

class Generator
{
public:
    Generator();
    std::unique_ptr<Result> generate(std::unique_ptr<Result> p_result);
private:
    virtual int calculate_column_count(int p_width, int p_size);
    virtual int calculate_line_count(int p_height, int p_size);
    virtual std::unique_ptr<Result> calculate_shapes_count(std::unique_ptr<Result> p_result);
    virtual std::vector<std::shared_ptr<Shape> > generate_vector();

    int m_shapes_count;
};

#endif // GENERATOR_H
