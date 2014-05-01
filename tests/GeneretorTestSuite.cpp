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
    std::unique_ptr<ResultMock> m_ResultMock;
};

void GeneretorTestSuite::SetUp()
{
    m_GeneratorTestable.reset(new GeneratorTestable);
    m_ResultMock.reset(new ResultMock);
}

void GeneretorTestSuite::TearDown()
{

}

TEST_F(GeneretorTestSuite, forBoard_2x1_AndFigureSize_1_VectorSizeIs_3)
{
    EXPECT_CALL(*m_ResultMock, get_width()).WillOnce(Return(2));
    EXPECT_CALL(*m_ResultMock, get_height()).WillOnce(Return(1));
    EXPECT_CALL(*m_ResultMock, get_size()).WillRepeatedly(Return(1));
    ASSERT_EQ((m_GeneratorTestable->generate(*m_ResultMock)).size(), 3);
}

TEST_F(GeneretorTestSuite, forBoard_100x200_AndFigureSize_20_VectorSizeIs_75)
{
    EXPECT_CALL(*m_ResultMock, get_width()).WillOnce(Return(100));
    EXPECT_CALL(*m_ResultMock, get_height()).WillOnce(Return(200));
    EXPECT_CALL(*m_ResultMock, get_size()).WillRepeatedly(Return(20));
    ASSERT_EQ((m_GeneratorTestable->generate(*m_ResultMock)).size(), 75);
}
