#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.h"

class Triangle : public Shape
{
public:
    Triangle();
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(bool** p_grid, int p_size, int p_x, int p_y);
    //virtual void fill_grid(std::vector<std::vector<bool>>& p_grid, int);
private:
    double prosta1(int, int);
    double prosta2(int, int);
};

#endif // TRIANGLE_H
