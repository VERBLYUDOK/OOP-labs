#include "gtest/gtest.h"
#include "decimal.h"

// Тест для конструкторов
TEST(DecimalTest, ConstructorFromString) {
    // Проверка корректного создания объекта
    Decimal D1("12345");
    EXPECT_EQ(D1.ToString(), "12345");

    // Проверка, что ведущие нули корректно удаляются
    Decimal D2("00012345");
    EXPECT_EQ(D2.ToString(), "12345");

    Decimal D3(4, '1');
    EXPECT_EQ(D3.ToString(), "1111");

    // Проверка удаления ведущих нулей
    Decimal D4{'0', '0', '0', '1', '2', '3'};
    EXPECT_EQ(D4.ToString(), "123");
}
// Тест оператора сложения
TEST(DecimalTest, Addition) {
    Decimal D1("12345");
    Decimal D2("54321");

    // Проверка результата сложения
    Decimal Result = D1 + D2;
    EXPECT_EQ(Result.ToString(), "66666");

    // Проверка +=
    D1 += D2;
    EXPECT_EQ(D1.ToString(), "66666");
}

// Тест оператора вычитания
TEST(DecimalTest, Subtraction) {
    Decimal D1("54321");
    Decimal D2("12345");

    // Проверка результата вычитания
    Decimal Result = D1 - D2;
    EXPECT_EQ(Result.ToString(), "41976");

    // Проверка -=
    D1 -= D2;
    EXPECT_EQ(D1.ToString(), "41976");
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}