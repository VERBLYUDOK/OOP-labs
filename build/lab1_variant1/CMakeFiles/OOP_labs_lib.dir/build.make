# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/lab1/build

# Include any dependencies generated for this target.
include lab1_variant1/CMakeFiles/OOP_labs_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lab1_variant1/CMakeFiles/OOP_labs_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include lab1_variant1/CMakeFiles/OOP_labs_lib.dir/progress.make

# Include the compile flags for this target's objects.
include lab1_variant1/CMakeFiles/OOP_labs_lib.dir/flags.make

lab1_variant1/CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.o: lab1_variant1/CMakeFiles/OOP_labs_lib.dir/flags.make
lab1_variant1/CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.o: /workspaces/lab1/lab1_variant1/src/countOnesBin.cpp
lab1_variant1/CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.o: lab1_variant1/CMakeFiles/OOP_labs_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lab1_variant1/CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.o"
	cd /workspaces/lab1/build/lab1_variant1 && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lab1_variant1/CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.o -MF CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.o.d -o CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.o -c /workspaces/lab1/lab1_variant1/src/countOnesBin.cpp

lab1_variant1/CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.i"
	cd /workspaces/lab1/build/lab1_variant1 && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/lab1/lab1_variant1/src/countOnesBin.cpp > CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.i

lab1_variant1/CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.s"
	cd /workspaces/lab1/build/lab1_variant1 && /usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/lab1/lab1_variant1/src/countOnesBin.cpp -o CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.s

# Object files for target OOP_labs_lib
OOP_labs_lib_OBJECTS = \
"CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.o"

# External object files for target OOP_labs_lib
OOP_labs_lib_EXTERNAL_OBJECTS =

lab1_variant1/libOOP_labs_lib.a: lab1_variant1/CMakeFiles/OOP_labs_lib.dir/src/countOnesBin.cpp.o
lab1_variant1/libOOP_labs_lib.a: lab1_variant1/CMakeFiles/OOP_labs_lib.dir/build.make
lab1_variant1/libOOP_labs_lib.a: lab1_variant1/CMakeFiles/OOP_labs_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libOOP_labs_lib.a"
	cd /workspaces/lab1/build/lab1_variant1 && $(CMAKE_COMMAND) -P CMakeFiles/OOP_labs_lib.dir/cmake_clean_target.cmake
	cd /workspaces/lab1/build/lab1_variant1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OOP_labs_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lab1_variant1/CMakeFiles/OOP_labs_lib.dir/build: lab1_variant1/libOOP_labs_lib.a
.PHONY : lab1_variant1/CMakeFiles/OOP_labs_lib.dir/build

lab1_variant1/CMakeFiles/OOP_labs_lib.dir/clean:
	cd /workspaces/lab1/build/lab1_variant1 && $(CMAKE_COMMAND) -P CMakeFiles/OOP_labs_lib.dir/cmake_clean.cmake
.PHONY : lab1_variant1/CMakeFiles/OOP_labs_lib.dir/clean

lab1_variant1/CMakeFiles/OOP_labs_lib.dir/depend:
	cd /workspaces/lab1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/lab1 /workspaces/lab1/lab1_variant1 /workspaces/lab1/build /workspaces/lab1/build/lab1_variant1 /workspaces/lab1/build/lab1_variant1/CMakeFiles/OOP_labs_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lab1_variant1/CMakeFiles/OOP_labs_lib.dir/depend

