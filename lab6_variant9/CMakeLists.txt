add_executable(lab6
    main.cpp
    src/npc.cpp
    src/elf.cpp
    src/dragon.cpp
    src/druid.cpp
    src/visitor.cpp
    src/observer.cpp
    src/factory.cpp
)

target_include_directories(lab6 PRIVATE include)

