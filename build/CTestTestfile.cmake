# CMake generated Testfile for 
# Source directory: /workspaces/lab1
# Build directory: /workspaces/lab1/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MyProjectTests "/workspaces/lab1/build/bin/tests_exe")
set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/lab1/CMakeLists.txt;34;add_test;/workspaces/lab1/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
