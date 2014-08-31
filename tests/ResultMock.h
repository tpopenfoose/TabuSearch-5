#pragma once

#include <gmock/gmock.h>
#include "result.h"

namespace Ut
{

class ResultMock : public Result
{
public:
    MOCK_CONST_METHOD1(waste, int(ConfigData));
    MOCK_CONST_METHOD0(getResult, std::vector<std::shared_ptr<Shape>>());
    MOCK_CONST_METHOD0(getRest, std::vector<std::shared_ptr<Shape>>());
    MOCK_CONST_METHOD0(getAll, std::vector<std::shared_ptr<Shape>>());
    MOCK_METHOD2(set_result, void(std::vector<std::shared_ptr<Shape>>, int));
};

typedef ::testing::StrictMock<ResultMock> StrictResultMock;

} //namespace Ut
