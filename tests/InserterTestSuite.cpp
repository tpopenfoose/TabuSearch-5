#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include <ResultMock.h>
#include <inserter.h>
#include <rectangle.h>
#include <generator.h>

using namespace testing;

class InserterTestSuite : public ::testing::Test
{
public:
    InserterTestSuite();

protected:
    Inserter inserter;
    std::shared_ptr<StrictResultMock> resultMock;
};

InserterTestSuite::InserterTestSuite()
    :   resultMock(std::make_shared<StrictResultMock>())
{
}

TEST_F(InserterTestSuite, test1)
{
    std::shared_ptr<Shape> shp1 = std::make_shared<Rectangle>();
    std::shared_ptr<Shape> shp2 = std::make_shared<Rectangle>();
    std::shared_ptr<Shape> shp3 = std::make_shared<Rectangle>();
    std::vector<std::shared_ptr<Shape>> result{shp1, shp2, shp3};

    ConfigData l_data(40,20,20,0,0,0,0);

    EXPECT_CALL(*resultMock, getAll()).WillOnce(Return(result));
    EXPECT_CALL(*resultMock, set_result(result, 2));
    inserter.insert(resultMock, l_data);
}
