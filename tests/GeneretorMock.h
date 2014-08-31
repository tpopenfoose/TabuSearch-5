#pragma once

#include <gmock/gmock.h>
#include "generator.h"

namespace Ut
{

class GeneratorMock : public Generator
{
public:
    MOCK_METHOD1(generate, std::vector<std::shared_ptr<Shape>>(const ConfigData&));
};

typedef ::testing::StrictMock<GeneratorMock> StrictGeneratorMock;

} //namespace Ut
