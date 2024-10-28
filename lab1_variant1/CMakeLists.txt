cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# превращает возможные предупреждения о неинициализированных переменных в ошибки компиляции


add_library(${CMAKE_PROJECT_NAME}_lib src/countOnesBin.cpp)
add_executable(lab1 main.cpp)

target_link_libraries(lab1 PRIVATE ${CMAKE_PROJECT_NAME}_lib)
