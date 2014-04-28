#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "generator.h"
#include <memory>

using namespace testing;

class GeneretorTestTestable : public Generator
{
public:
    MOCK_METHOD2(calculate_column_count, int(int, int));
    MOCK_METHOD2(calculate_line_count, int(int, int));
};

class GeneretorTestTestSuite : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

protected:
    std::shared_ptr<GeneretorTestTestable> m_sut;
};

void GeneretorTestTestSuite::SetUp()
{
    m_sut.reset(new GeneretorTestTestable);
}

void GeneretorTestTestSuite::TearDown()
{

}

TEST_F(GeneretorTestTestSuite, tes1)
{
    std::unique_ptr<Result> temp;
    EXPECT_CALL(*m_sut, calculate_column_count(10,2)).WillOnce(Return(5));
    m_sut->generate(std::move(temp));
}
