#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "generator.h"
#include <memory>
#include "GeneretorMock.h"
#include "ResultMock.h"
#include "ShapeMock.h"

using namespace testing;

class GeneratorTestable : public Generator
{

};

class GeneretorTestSuite : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

protected:
    std::shared_ptr<GeneratorTestable> m_GeneratorTestable;
    std::shared_ptr<Shape> m_ShapeMock;
    std::unique_ptr<ResultMock> m_ResultMock;
};

void GeneretorTestSuite::SetUp()
{
    m_GeneratorTestable.reset(new GeneratorTestable);
    m_ResultMock.reset(new ResultMock);
    m_ShapeMock.reset(new ShapeMock);
}

void GeneretorTestSuite::TearDown()
{

}

TEST_F(GeneretorTestSuite, tes1)
{
    EXPECT_CALL(*m_ResultMock, get_width()).WillOnce(Return(2));
    EXPECT_CALL(*m_ResultMock, get_size()).WillRepeatedly(Return(1));
    EXPECT_CALL(*m_ResultMock, get_height()).WillOnce(Return(1));
    Result actual;
    actual.set_all(m_GeneratorTestable->generate(*m_ResultMock));
    ASSERT_EQ(actual.getAll().size(), 3);
}
