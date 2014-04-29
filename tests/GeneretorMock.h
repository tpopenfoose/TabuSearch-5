#ifndef GENERETORMOCK_H
#define GENERETORMOCK_H
#include <gmock/gmock.h>
#include "generator.h"

class GeneratorMock : public Generator
{
public:
    MOCK_METHOD1(generate_, Result*(Result*));
    std::unique_ptr<Result> generate(std::unique_ptr<Result> p_result) {
        return std::unique_ptr<Result>(generate_(p_result.get()));
    }

    MOCK_METHOD1(calculate_shapes_count, int(const Result &));
    MOCK_METHOD2(calculate_column_count, int(int, int));
    MOCK_METHOD2(calculate_line_count, int(int, int));
    MOCK_METHOD0(generate_vector, std::vector<std::shared_ptr<Shape>>());
};

#endif // GENERETORMOCK_H
