set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")

add_executable(lab7
    main.cpp
    src/npc.cpp
    src/elf.cpp
    src/dragon.cpp
    src/druid.cpp
    src/visitor.cpp
    src/observer.cpp
    src/factory.cpp
    src/logger.cpp
    src/scheduler.cpp
)

target_include_directories(lab7 PRIVATE include)

target_link_libraries(lab7 pthread)


