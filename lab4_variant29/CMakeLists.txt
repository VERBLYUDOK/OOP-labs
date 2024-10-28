add_executable(lab4 main.cpp src/Figure.tpp src/Hexagon.tpp src/Pentagon.tpp src/Rhombus.tpp include/Figure.h include/Hexagon.h include/Pentagon.h include/Rhombus.h include/Point.h include/Array.h src/Array.tpp src/Point.tpp)

target_include_directories(lab4 PRIVATE include)