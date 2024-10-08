#include <Figure.h>
#include <Rhombus.h>
#include <Pentagon.h>
#include <Hexagon.h>
#include <gtest/gtest.h>

TEST(RhombusTest, AreaCalculation) {
    double x_coords[] = {0.0, 2.0, 4.0, 2.0};
    double y_coords[] = {2.0, 4.0, 2.0, 0.0};

    Rhombus Rhombus(x_coords, y_coords);

    double expected_area = 8.0;
    double calculated_area = static_cast<double>(Rhombus); // Rhombus.Area()

    EXPECT_DOUBLE_EQ(calculated_area, expected_area);
}
TEST(RhombusTest, CenterCalculation) {
    double x_coords[] = {0.0, 2.0, 4.0, 2.0};
    double y_coords[] = {2.0, 4.0, 2.0, 0.0};

    Rhombus Rhombus(x_coords, y_coords);
    Rhombus.CalculateCenter();

    double expected_center_x = 2.0;
    double expected_center_y = 2.0;

    EXPECT_DOUBLE_EQ(Rhombus.getCenterX(), expected_center_x);
    EXPECT_DOUBLE_EQ(Rhombus.getCenterY(), expected_center_y);
}

TEST(RhombusTest, EqualityOperator) {
    double x_coords1[] = {0.0, 2.0, 4.0, 2.0};
    double y_coords1[] = {2.0, 4.0, 2.0, 0.0};

    double x_coords2[] = {0.0, 2.0, 4.0, 2.0};
    double y_coords2[] = {2.0, 4.0, 2.0, 0.0};

    Rhombus Rhombus1(x_coords1, y_coords1);
    Rhombus Rhombus2(x_coords2, y_coords2);

    EXPECT_TRUE(Rhombus1 == Rhombus2);
}

TEST(PentagonTest, AreaCalculation) {
    double x_coords[] = {0.0, 2.0, 3.0, 1.5, -0.5};
    double y_coords[] = {0.0, 0.0, 2.0, 3.5, 2.0};

    Pentagon Pentagon(x_coords, y_coords);

    double expected_area = 8.125;
    double calculated_area = Pentagon.Area();

    EXPECT_DOUBLE_EQ(calculated_area, expected_area);
}

TEST(HexagonTest, AssignmentOperator) {
    double x_coords[] = {0, 1, 2, 2, 1, 0};
    double y_coords[] = {0, 0, 1, 2, 2, 1};

    Figure* Hex1 = new Hexagon(x_coords, y_coords);
    Figure* Hex2 = new Hexagon();

    *Hex2 = *Hex1;

    EXPECT_TRUE(*Hex1 == *Hex2);

    delete Hex1;
    delete Hex2;
}

TEST(RhombusTest, InvalidAssignment) {
    Rhombus Rhombus;
    Pentagon Pentagon;

    EXPECT_THROW({
        Rhombus = Pentagon;
    }, std::invalid_argument);
}

TEST(HexagonTest, MoveAssignmentOperator) {
    double x_coords[] = {0, 1, 2, 2, 1, 0};
    double y_coords[] = {0, 0, 1, 2, 2, 1};

    Figure* hex1 = new Hexagon(x_coords, y_coords);

    Figure* hex2 = new Hexagon();

    *hex2 = std::move(*hex1);

    Hexagon expected_hex(x_coords, y_coords);
    EXPECT_TRUE(*hex2 == expected_hex);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
