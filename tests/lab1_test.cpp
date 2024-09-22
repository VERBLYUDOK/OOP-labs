#include <gtest/gtest.h>
#include "../lab1_variant1/include/foo.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(countOnesBin(2, 7) == 11);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(countOnesBin(1, 7) == 12);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(countOnesBin(0, 7) == 12);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}