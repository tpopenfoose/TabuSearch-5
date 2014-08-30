#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include <inserter.h>
#include <rectangle.h>

namespace Ut
{

using namespace testing;

class InserterTestSuite : public Test
{
protected:
    Inserter inserter;
};

TEST_F(InserterTestSuite, shouldReturnProperShapseForGivenData)
{
    std::shared_ptr<Shape> shp1 = std::make_shared<Rectangle>();
    std::shared_ptr<Shape> shp2 = std::make_shared<Rectangle>();
    std::shared_ptr<Shape> shp3 = std::make_shared<Rectangle>();
    std::vector<std::shared_ptr<Shape>> result{shp1, shp2, shp3};

    ConfigData l_data(40,20,20,0,0,0,0);
    Shapes l_expectedShapes = inserter.insert(result, l_data);

    ASSERT_EQ(l_expectedShapes.second, 2);
}

} //namespace Ut
