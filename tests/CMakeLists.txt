cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# превращает возможные предупреждения о неинициализированных переменных в ошибки компиляции

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(lab1_test lab1_test.cpp)
target_link_libraries(lab1_test ${CMAKE_PROJECT_NAME}_lib gtest_main)

add_executable(lab2_test lab2_test.cpp ../lab2_variant1/src/decimal.cpp ../lab2_variant1/include/decimal.h)
target_include_directories(lab2_test PRIVATE ../lab2_variant1/include)
target_link_libraries(lab2_test gtest_main)

add_executable(lab3_test lab3_test.cpp ../lab3_variant29/src/Figure.cpp ../lab3_variant29/src/Rhombus.cpp ../lab3_variant29/src/Pentagon.cpp ../lab3_variant29/src/Hexagon.cpp ../lab3_variant29/include/Figure.h ../lab3_variant29/include/Rhombus.h ../lab3_variant29/include/Pentagon.h ../lab3_variant29/include/Hexagon.h)
target_include_directories(lab3_test PRIVATE ../lab3_variant29/include)
target_link_libraries(lab3_test PRIVATE gtest_main)

add_executable(lab4_test lab4_test.cpp ../lab4_variant29/src/Figure.tpp ../lab4_variant29/src/Hexagon.tpp ../lab4_variant29/src/Pentagon.tpp ../lab4_variant29/src/Rhombus.tpp ../lab4_variant29/include/Figure.h ../lab4_variant29/include/Hexagon.h ../lab4_variant29/include/Pentagon.h ../lab4_variant29/include/Rhombus.h ../lab4_variant29/include/Point.h ../lab4_variant29/include/Array.h ../lab4_variant29/src/Array.tpp ../lab4_variant29/src/Point.tpp)
target_include_directories(lab4_test PRIVATE ../lab4_variant29/include)
target_link_libraries(lab4_test PRIVATE gtest_main)

add_executable(lab5_test lab5_test.cpp ../lab5_variant1/src/FixedMemoryResource.cpp ../lab5_variant1/src/PmrVector.tpp ../lab5_variant1/include/FixedMemoryResource.h ../lab5_variant1/include/PmrVector.h)
target_include_directories(lab5_test PRIVATE ../lab5_variant1/include)
target_link_libraries(lab5_test PRIVATE gtest_main)

add_executable(lab6_test
    lab6_test.cpp
    ../lab6_variant9/src/npc.cpp
    ../lab6_variant9/src/elf.cpp
    ../lab6_variant9/src/dragon.cpp
    ../lab6_variant9/src/druid.cpp
    ../lab6_variant9/src/visitor.cpp
    ../lab6_variant9/src/observer.cpp
    ../lab6_variant9/src/factory.cpp
)
target_include_directories(lab6_test PRIVATE ../lab6_variant9/include)
target_link_libraries(lab6_test PRIVATE gtest_main)

add_executable(lab7_test
    lab7_test.cpp
    ../lab7_variant9/src/npc.cpp
    ../lab7_variant9/src/elf.cpp
    ../lab7_variant9/src/dragon.cpp
    ../lab7_variant9/src/druid.cpp
    ../lab7_variant9/src/visitor.cpp
    ../lab7_variant9/src/observer.cpp
    ../lab7_variant9/src/factory.cpp
    ../lab7_variant9/src/logger.cpp
    ../lab7_variant9/src/scheduler.cpp
)
target_include_directories(lab7_test PRIVATE ../lab7_variant9/include)
target_link_libraries(lab7_test PRIVATE gtest_main pthread)

# Добавление тестов в тестовый набор
add_test(NAME lab1_test COMMAND lab1_test)
add_test(NAME lab2_test COMMAND lab2_test)
add_test(NAME lab3_test COMMAND lab3_test)
add_test(NAME lab4_test COMMAND lab4_test)
add_test(NAME lab5_test COMMAND lab5_test)
add_test(NAME lab6_test COMMAND lab6_test)
add_test(NAME lab7_test COMMAND lab6_test)

gtest_discover_tests(lab1_test)
gtest_discover_tests(lab2_test)
gtest_discover_tests(lab3_test)
gtest_discover_tests(lab4_test)
gtest_discover_tests(lab5_test)
gtest_discover_tests(lab6_test)
gtest_discover_tests(lab7_test)