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

add_executable(lab1_test lab1_test.cpp)
target_link_libraries(lab1_test ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND lab1_test)