#pragma once

#include <gmock/gmock.h>
#include <IGrid.h>

namespace Ut
{

class GridMock : public IGrid
{
public:
    MOCK_METHOD2(create, void(int, int));
    MOCK_METHOD0(deleteAll, void());
    MOCK_METHOD0(clear, void());
    MOCK_METHOD0(getGrid, Matrix&());
    MOCK_METHOD2(at, bool(int, int));
};

typedef ::testing::StrictMock<GridMock> StrictGridMock;

} //namespace Ut
