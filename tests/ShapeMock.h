#ifndef SHAPEMOCK_H
#define SHAPEMOCK_H
#include <gmock/gmock.h>
#include "shape.h"

class ShapeMock : public Shape
{
public:
    MOCK_METHOD3(draw, void(QPainter &, int, int));
    MOCK_METHOD1(get_area, double(int));
    MOCK_METHOD2(fill_grid, void(bool**, int));
    MOCK_METHOD1(set_x, void(int));
    MOCK_METHOD1(set_y, void(int));
};

#endif // SHAPEMOCK_H
