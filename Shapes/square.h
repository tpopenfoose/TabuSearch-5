#ifndef SQUARE_H
#define SQUARE_H
#include "shape.h"

class Square : public Shape
{
public:
    Square();
    virtual void draw(QPainter &, int, int);
    virtual double get_area(int);
    virtual void fill_grid(bool**, int);
    //virtual void fill_grid(std::vector<std::vector<bool>>& p_grid, int);
};

#endif // SQUARE_H
