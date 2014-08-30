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
    Shapes l_reveivedShapes = inserter.insert(result, l_data);

    std::shared_ptr<Shape> expectedShp1 = std::make_shared<Rectangle>();
    expectedShp1->set_x(0);
    expectedShp1->set_y(0);
    std::shared_ptr<Shape> expectedShp2 = std::make_shared<Rectangle>();
    expectedShp2->set_x(20);
    expectedShp2->set_y(0);
    std::shared_ptr<Shape> expectedShp3 = std::make_shared<Rectangle>();
    expectedShp3->set_x(0);
    expectedShp3->set_y(0);

    Shapes l_expectedShapes{{expectedShp1, expectedShp2, expectedShp3}, 2};

    for(auto iter1 = l_expectedShapes.first.begin(), iter2 = l_reveivedShapes.first.begin();
        iter1 != l_expectedShapes.first.end() && iter2 != l_reveivedShapes.first.end();
        ++iter1, ++iter2)
    {
        std::shared_ptr<Shape> s1 = *iter1;
        std::shared_ptr<Shape> s2 = *iter2;
        ASSERT_EQ(*s1, *s2);
    }
}

} //namespace Ut
