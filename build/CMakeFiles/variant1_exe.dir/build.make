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
include CMakeFiles/variant1_exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/variant1_exe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/variant1_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/variant1_exe.dir/flags.make

CMakeFiles/variant1_exe.dir/variant1/main.cpp.o: CMakeFiles/variant1_exe.dir/flags.make
CMakeFiles/variant1_exe.dir/variant1/main.cpp.o: /workspaces/lab1/variant1/main.cpp
CMakeFiles/variant1_exe.dir/variant1/main.cpp.o: CMakeFiles/variant1_exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/variant1_exe.dir/variant1/main.cpp.o"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/variant1_exe.dir/variant1/main.cpp.o -MF CMakeFiles/variant1_exe.dir/variant1/main.cpp.o.d -o CMakeFiles/variant1_exe.dir/variant1/main.cpp.o -c /workspaces/lab1/variant1/main.cpp

CMakeFiles/variant1_exe.dir/variant1/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/variant1_exe.dir/variant1/main.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/lab1/variant1/main.cpp > CMakeFiles/variant1_exe.dir/variant1/main.cpp.i

CMakeFiles/variant1_exe.dir/variant1/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/variant1_exe.dir/variant1/main.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/lab1/variant1/main.cpp -o CMakeFiles/variant1_exe.dir/variant1/main.cpp.s

# Object files for target variant1_exe
variant1_exe_OBJECTS = \
"CMakeFiles/variant1_exe.dir/variant1/main.cpp.o"

# External object files for target variant1_exe
variant1_exe_EXTERNAL_OBJECTS =

bin/variant1_exe: CMakeFiles/variant1_exe.dir/variant1/main.cpp.o
bin/variant1_exe: CMakeFiles/variant1_exe.dir/build.make
bin/variant1_exe: libvariant1_lib.a
bin/variant1_exe: CMakeFiles/variant1_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/variant1_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/variant1_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/variant1_exe.dir/build: bin/variant1_exe
.PHONY : CMakeFiles/variant1_exe.dir/build

CMakeFiles/variant1_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/variant1_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/variant1_exe.dir/clean

CMakeFiles/variant1_exe.dir/depend:
	cd /workspaces/lab1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/lab1 /workspaces/lab1 /workspaces/lab1/build /workspaces/lab1/build /workspaces/lab1/build/CMakeFiles/variant1_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/variant1_exe.dir/depend
