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

# Добавление тестов в тестовый набор
add_test(NAME lab1_test COMMAND lab1_test)
add_test(NAME lab2_test COMMAND lab2_test)
add_test(NAME lab3_test COMMAND lab3_test)

gtest_discover_tests(lab1_test)
gtest_discover_tests(lab2_test)
gtest_discover_tests(lab3_test)