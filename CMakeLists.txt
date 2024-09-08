cmake_minimum_required(VERSION 3.10)
project(variant1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# превращает возможные предупреждения о неинициализированных переменных в ошибки компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

FetchContent_MakeAvailable(googletest)

add_library(${CMAKE_PROJECT_NAME}_lib variant1/src/countOnesBin.cpp)
add_executable(${CMAKE_PROJECT_NAME}_exe variant1/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

enable_testing()

add_executable(tests_exe variant1/test/test1.cpp)
target_link_libraries(tests_exe ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests_exe)