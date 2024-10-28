#include <Figure.h>
#include <Rhombus.h>
#include <Pentagon.h>
#include <Hexagon.h>
#include <gtest/gtest.h>

TEST(RhombusTest, AreaCalculation) {
    using T = double;

    std::array<Point<T>, 4> vertices = {
        Point<T>(0.0, 2.0),
        Point<T>(2.0, 4.0),
        Point<T>(4.0, 2.0),
        Point<T>(2.0, 0.0)
    };

    Rhombus<T> rhombus(vertices);

    double expected_area = 8.0;
    double calculated_area = static_cast<double>(rhombus);

    EXPECT_DOUBLE_EQ(calculated_area, expected_area);
}

TEST(RhombusTest, CenterCalculation) {
    using T = double;
    std::array<Point<T>, 4> vertices = {
        Point<T>(0.0, 2.0),
        Point<T>(2.0, 4.0),
        Point<T>(4.0, 2.0),
        Point<T>(2.0, 0.0)
    };

    Rhombus<T> rhombus(vertices);
    rhombus.CalculateCenter();

    T expected_center_x = 2.0;
    T expected_center_y = 2.0;

    EXPECT_DOUBLE_EQ(rhombus.GetCenter().getX(), expected_center_x);
    EXPECT_DOUBLE_EQ(rhombus.GetCenter().getY(), expected_center_y);
}

TEST(RhombusTest, EqualityOperator) {
    using T = double;
    std::array<Point<T>, 4> vertices1 = {
        Point<T>(0.0, 2.0),
        Point<T>(2.0, 4.0),
        Point<T>(4.0, 2.0),
        Point<T>(2.0, 0.0)
    };

    std::array<Point<T>, 4> vertices2 = vertices1;

    Rhombus<T> rhombus1(vertices1);
    Rhombus<T> rhombus2(vertices2);

    EXPECT_TRUE(rhombus1 == rhombus2);
}

TEST(PentagonTest, AreaCalculation) {
    using T = double;
    std::array<Point<T>, 5> vertices = {
        Point<T>(0.0, 0.0),
        Point<T>(2.0, 0.0),
        Point<T>(3.0, 2.0),
        Point<T>(1.5, 3.5),
        Point<T>(-0.5, 2.0)
    };

    Pentagon<T> pentagon(vertices);

    double expected_area = 8.125;
    double calculated_area = pentagon.Area();

    EXPECT_DOUBLE_EQ(calculated_area, expected_area);
}

TEST(HexagonTest, AssignmentOperator) {
    using T = double;
    std::array<Point<T>, 6> vertices = {
        Point<T>(0.0, 0.0),
        Point<T>(1.0, 0.0),
        Point<T>(2.0, 1.0),
        Point<T>(2.0, 2.0),
        Point<T>(1.0, 2.0),
        Point<T>(0.0, 1.0)
    };

    Hexagon<T> hex1(vertices);
    Hexagon<T> hex2;

    hex2 = hex1;

    EXPECT_TRUE(hex1 == hex2);
}

TEST(RhombusTest, InvalidAssignment) {
    using T = double;
    Rhombus<T> rhombus;
    Pentagon<T> pentagon;

    EXPECT_THROW({
        rhombus = pentagon;
    }, std::invalid_argument);
}

TEST(HexagonTest, MoveAssignmentOperator) {
    using T = double;
    std::array<Point<T>, 6> vertices = {
        Point<T>(0.0, 0.0),
        Point<T>(1.0, 0.0),
        Point<T>(2.0, 1.0),
        Point<T>(2.0, 2.0),
        Point<T>(1.0, 2.0),
        Point<T>(0.0, 1.0)
    };

    Hexagon<T> hex1(vertices);
    Hexagon<T> hex2;

    hex2 = std::move(hex1);

    Hexagon<T> expected_hex(vertices);
    EXPECT_TRUE(hex2 == expected_hex);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
