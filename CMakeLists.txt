cmake_minimum_required(VERSION 3.10)
project(OOP_labs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# превращает возможные предупреждения о неинициализированных переменных в ошибки компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(tests)
add_subdirectory(lab1_variant1)
add_subdirectory(lab2_variant1)
add_subdirectory(lab3_variant29)
add_subdirectory(lab4_variant29)
add_subdirectory(lab5_variant1)
add_subdirectory(lab6_variant9)
