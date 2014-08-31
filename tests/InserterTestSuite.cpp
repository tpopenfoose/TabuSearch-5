#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <GridMock.h>

#include <inserter.h>
#include <rectangle.h>
#include <triangle.h>
#include <square.h>
#include <circle.h>

namespace Ut
{

using namespace testing;

class InserterTestable : public Inserter
{
public:
    InserterTestable()
    {
//        grid = std::unique_ptr<StrictGridMock>(new StrictGridMock);
//        f_grid = std::unique_ptr<StrictGridMock>(new StrictGridMock);
    }

};

class InserterTestSuite : public Test
{
protected:
    InserterTestable inserter;
};

MATCHER_P(VectorOfSharedPointersMacher, value, "")
{
    int i = 0;
    bool pass = true;
    *result_listener << "\n" <<"List of NOT mached items: " << "\n";
    for(auto iter1 = arg.begin(), iter2 = value.begin();
        iter1 != arg.end() && iter2 != value.end();
        ++iter1, ++iter2)
    {
        i++;
        auto actual = *iter1;
        auto expected = *iter2;

        if(*expected != *actual)
        {
            *result_listener << "position: " << PrintToString(i) << ", "
                             << "Expected " << expected->value() << "; " << "Actual " << actual->value()
                             << "\n";
            pass = false;
        }
    }
    return pass;
}

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

    EXPECT_THAT(l_reveivedShapes.first, VectorOfSharedPointersMacher(l_expectedShapes.first));
    ASSERT_EQ(l_reveivedShapes.second, l_expectedShapes.second);
}

TEST_F(InserterTestSuite, shouldReturnProperShapseForGivenData2)
{
    std::shared_ptr<Shape> shp1 = std::make_shared<Square>();
    std::shared_ptr<Shape> shp2 = std::make_shared<Square>();
    std::shared_ptr<Shape> shp3 = std::make_shared<Square>();
    std::vector<std::shared_ptr<Shape>> result{shp1, shp2, shp3};

    ConfigData l_data(40,20,20,0,0,0,0);
    Shapes l_reveivedShapes = inserter.insert(result, l_data);

    std::shared_ptr<Shape> expectedShp1 = std::make_shared<Square>();
    expectedShp1->set_x(0);
    expectedShp1->set_y(0);
    std::shared_ptr<Shape> expectedShp2 = std::make_shared<Square>();
    expectedShp2->set_x(20);
    expectedShp2->set_y(0);
    std::shared_ptr<Shape> expectedShp3 = std::make_shared<Square>();
    expectedShp3->set_x(0);
    expectedShp3->set_y(0);

    Shapes l_expectedShapes{{expectedShp1, expectedShp2, expectedShp3}, 2};

    EXPECT_THAT(l_reveivedShapes.first, VectorOfSharedPointersMacher(l_expectedShapes.first));
    ASSERT_EQ(l_reveivedShapes.second, l_expectedShapes.second);
}

//TEST_F(InserterTestSuite, shouldReturnProperShapseForGivenData3)
//{
//    std::shared_ptr<Shape> shp1 = std::make_shared<Triangle>();
//    std::shared_ptr<Shape> shp2 = std::make_shared<Triangle>();
//    std::shared_ptr<Shape> shp3 = std::make_shared<Triangle>();
//    std::vector<std::shared_ptr<Shape>> result{shp1, shp2, shp3};

//    ConfigData l_data(40,20,20,0,0,0,0);
//    Shapes l_reveivedShapes = inserter.insert(result, l_data);

//    std::shared_ptr<Shape> expectedShp1 = std::make_shared<Triangle>();
//    expectedShp1->set_x(0);
//    expectedShp1->set_y(0);
//    std::shared_ptr<Shape> expectedShp2 = std::make_shared<Triangle>();
//    expectedShp2->set_x(20);
//    expectedShp2->set_y(0);
//    std::shared_ptr<Shape> expectedShp3 = std::make_shared<Triangle>();
//    expectedShp3->set_x(0);
//    expectedShp3->set_y(0);

//    Shapes l_expectedShapes{{expectedShp1, expectedShp2, expectedShp3}, 2};

//    EXPECT_THAT(l_reveivedShapes.first, VectorOfSharedPointersMacher(l_expectedShapes.first));
//    ASSERT_EQ(l_reveivedShapes.second, l_expectedShapes.second);
//}

} //namespace Ut
