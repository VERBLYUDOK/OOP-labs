#include <gtest/gtest.h>
#include <PmrVector.h>
#include <FixedMemoryResource.h>

TEST(PmrVectorTest, IntPushBackAndAccess) {
    FixedMemoryResource memoryResource(1024);

    PmrVector<int> vec(&memoryResource);

    vec.push_back(5);
    vec.push_back(10);
    vec.push_back(15);

    ASSERT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 10);
    EXPECT_EQ(vec[2], 15);
}

TEST(PmrVectorTest, IntPopBack) {
    FixedMemoryResource memoryResource(1024);

    PmrVector<int> vec(&memoryResource);

    vec.push_back(100);
    vec.push_back(200);

    vec.pop_back();

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 100);
}

struct MyStruct {
    int a;
    double b;
    std::string c;

    MyStruct(int a_, double b_, const std::string& c_) : a(a_), b(b_), c(c_) {}
};

TEST(PmrVectorTest, MyStructPushBackAndAccess) {
    FixedMemoryResource memoryResource(2048);

    PmrVector<MyStruct> vec(&memoryResource);

    vec.push_back(MyStruct(1, 1.1, "one"));
    vec.push_back(MyStruct(2, 2.2, "two"));
    vec.push_back(MyStruct(3, 3.3, "three"));

    ASSERT_EQ(vec.size(), 3);

    EXPECT_EQ(vec[0].a, 1);
    EXPECT_DOUBLE_EQ(vec[0].b, 1.1);
    EXPECT_EQ(vec[0].c, "one");

    EXPECT_EQ(vec[1].a, 2);
    EXPECT_DOUBLE_EQ(vec[1].b, 2.2);
    EXPECT_EQ(vec[1].c, "two");

    EXPECT_EQ(vec[2].a, 3);
    EXPECT_DOUBLE_EQ(vec[2].b, 3.3);
    EXPECT_EQ(vec[2].c, "three");
}

TEST(PmrVectorTest, IteratorTraversal) {
    FixedMemoryResource memoryResource(1024);

    PmrVector<int> vec(&memoryResource);

    for (int i = 0; i < 5; ++i) {
        vec.push_back(i * 10);
    }

    int expectedValue = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        EXPECT_EQ(*it, expectedValue);
        expectedValue += 10;
    }
}

TEST(PmrVectorTest, ConstIteratorTraversal) {
    FixedMemoryResource memoryResource(1024);

    PmrVector<int> vec(&memoryResource);
    vec.push_back(50);
    vec.push_back(60);

    const PmrVector<int>& constVec = vec;

    int expectedValues[] = {50, 60};
    int index = 0;

    for (auto it = constVec.begin(); it != constVec.end(); ++it) {
        EXPECT_EQ(*it, expectedValues[index++]);
    }
}

TEST(FixedMemoryResourceTest, ReuseDeallocatedMemory) {
    FixedMemoryResource memoryResource(1024);

    void* firstDataPtr = nullptr;
    {
        PmrVector<int> vec(&memoryResource);

        for (int i = 0; i < 10; ++i) {
            vec.push_back(i);
        }

        ASSERT_EQ(vec.size(), 10);

        // Сохраняем указатель на данные первого вектора
        firstDataPtr = vec.data();
    } // Первый вектор выходит из области видимости и освобождает память

    void* secondDataPtr = nullptr;
    {
        PmrVector<int> vec(&memoryResource);

        for (int i = 0; i < 10; ++i) {
            vec.push_back(i + 100);
        }

        ASSERT_EQ(vec.size(), 10);

        // Сохраняем указатель на данные второго вектора
        secondDataPtr = vec.data();

        // Проверяем, что адреса совпадают, то есть память переиспользуется
        EXPECT_EQ(firstDataPtr, secondDataPtr);

        EXPECT_EQ(vec[0], 100);
        EXPECT_EQ(vec[9], 109);
    }
}

TEST(FixedMemoryResourceTest, AllocationFailure) {
    FixedMemoryResource memoryResource(128);

    PmrVector<int> vec(&memoryResource);

    // Больше элементов, чем может поместиться в выделенной памяти
    EXPECT_THROW({
        for (int i = 0; i < 1000; ++i) {
            vec.push_back(i);
        }
    }, std::bad_alloc);
}

TEST(PmrVectorTest, ReallocatePreservesData) {
    FixedMemoryResource memoryResource(2048);

    PmrVector<int> vec(&memoryResource);

    size_t previousCapacity = vec.capacity();

    for (int i = 0; i < 15; ++i) {
        vec.push_back(i * 2);

        if (vec.capacity() != previousCapacity) {
            // Емкость изменилась
            std::cout << "Capacity increased from " << previousCapacity << " to " << vec.capacity() << std::endl;
            previousCapacity = vec.capacity();
        }
    }

    ASSERT_EQ(vec.size(), 15);

    for (int i = 0; i < 15; ++i) {
        EXPECT_EQ(vec[i], i * 2);
    }
}

TEST(PmrVectorTest, DifferentDataTypes) {
    FixedMemoryResource memoryResource(4096);

    // Тест с типом double
    PmrVector<double> vecDouble(&memoryResource);
    vecDouble.push_back(1.5);
    vecDouble.push_back(2.5);
    vecDouble.push_back(3.5);

    ASSERT_EQ(vecDouble.size(), 3);
    EXPECT_DOUBLE_EQ(vecDouble[0], 1.5);
    EXPECT_DOUBLE_EQ(vecDouble[1], 2.5);
    EXPECT_DOUBLE_EQ(vecDouble[2], 3.5);

    // Тест с типом std::string
    PmrVector<std::string> vecString(&memoryResource);
    vecString.push_back("Test1");
    vecString.push_back("Test2");

    ASSERT_EQ(vecString.size(), 2);
    EXPECT_EQ(vecString[0], "Test1");
    EXPECT_EQ(vecString[1], "Test2");
}

TEST(PmrVectorTest, OutOfRangeAccess) {
    FixedMemoryResource memoryResource(1024);

    PmrVector<int> vec(&memoryResource);

    vec.push_back(5);
    vec.push_back(10);

    EXPECT_NO_THROW({
        int value = vec[1];
    });

    // Проверяем некорректный доступ
    EXPECT_THROW({
        int value = vec[2];
    }, std::out_of_range);

    EXPECT_THROW({
        int value = vec[-1];
    }, std::out_of_range);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}