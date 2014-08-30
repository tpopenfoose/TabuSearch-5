#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <generator.h>

using namespace testing;

struct GeneretorTestSuite : public ::testing::Test
{
    Generator generator;
};

struct ConfigDataTestStructure
{
    ConfigDataTestStructure(ConfigData data, int expectedSize)
        :   data(data), expectedSize(expectedSize)
    {
    }
    ConfigData data;
    int expectedSize;
};

struct GeneretorTestSuiteWithParam : public GeneretorTestSuite,
                                     public ::WithParamInterface<ConfigDataTestStructure>
{
};

INSTANTIATE_TEST_CASE_P(InstantiationName,
                        GeneretorTestSuiteWithParam,
                        Values(
                            ConfigDataTestStructure(ConfigData(2,1,1,0,0,0,0), 3),
                            ConfigDataTestStructure(ConfigData(100,200,20,0,0,0,0), 75),
                            ConfigDataTestStructure(ConfigData(40,20,20,0,0,0,0), 3)));

TEST_P(GeneretorTestSuiteWithParam, shouldReturnRightNumberOfShapesOnGivenConfigData)
{
    ASSERT_EQ((generator.generate(GetParam().data)).size(), GetParam().expectedSize);
}
