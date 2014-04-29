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
    virtual std::vector<std::shared_ptr<Shape> > generate(const Result & p_result);
protected:
    virtual int calculate_column_count(int p_width, int p_size);
    virtual int calculate_line_count(int p_height, int p_size);
    virtual int calculate_shapes_count(const Result & p_result);
    virtual std::vector<std::shared_ptr<Shape> > generate_vector(int p_shapes_count);
};

#endif // GENERATOR_H
