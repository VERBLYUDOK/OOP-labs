add_executable(lab5 main.cpp src/PmrVector.tpp include/PmrVector.h src/FixedMemoryResource.cpp include/FixedMemoryResource.h)

target_include_directories(lab5 PRIVATE include)