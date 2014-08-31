#pragma once

#include <gmock/gmock.h>
#include "shape.h"

namespace Ut
{

class ShapeMock : public Shape
{
public:
    MOCK_METHOD3(draw, void(QPainter &, int, int));
    MOCK_METHOD1(get_area, double(int));
    MOCK_METHOD2(fill_grid, void(bool**, int));
    MOCK_METHOD1(set_x, void(int));
    MOCK_METHOD1(set_y, void(int));
};

typedef ::testing::StrictMock<ShapeMock> StrictShapeMock;

} //namespace Ut
