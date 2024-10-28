add_executable(lab3 main.cpp src/Figure.cpp src/Hexagon.cpp src/Pentagon.cpp src/Rhombus.cpp include/Figure.h include/Hexagon.h include/Pentagon.h include/Rhombus.h)

target_include_directories(lab3 PRIVATE include)