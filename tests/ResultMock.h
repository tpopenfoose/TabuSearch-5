#ifndef RESULTMOCK_H
#define RESULTMOCK_H

#include <gmock/gmock.h>
#include "result.h"

class ResultMock : public Result
{
public:
    MOCK_METHOD0(getResult, std::vector<std::shared_ptr<Shape>>());
    MOCK_METHOD0(getRest, std::vector<std::shared_ptr<Shape>>());
    MOCK_METHOD0(getAll, std::vector<std::shared_ptr<Shape>>());
    MOCK_METHOD1(set_result, void(std::vector<std::shared_ptr<Shape>>));
    MOCK_METHOD1(set_rest, void(std::vector<std::shared_ptr<Shape>>));
    MOCK_METHOD1(set_all, void(std::vector<std::shared_ptr<Shape>>));
    MOCK_METHOD1(set_data, void(ConfigData));
    MOCK_CONST_METHOD0(get_size, int());
    MOCK_CONST_METHOD0(get_width, int());
    MOCK_CONST_METHOD0(get_height, int());
    MOCK_METHOD0(get_tabusize, int());
    MOCK_METHOD0(get_iteration, int());
    MOCK_METHOD0(get_tabutime, int());
    MOCK_CONST_METHOD0(get_procent, int());
};

#endif // RESULTMOCK_H
