# CMake generated Testfile for 
# Source directory: /workspaces/lab1/tests
# Build directory: /workspaces/lab1/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/workspaces/lab1/build/tests/lab1_test[1]_include.cmake")
include("/workspaces/lab1/build/tests/lab2_test[1]_include.cmake")
include("/workspaces/lab1/build/tests/lab3_test[1]_include.cmake")
add_test(lab1_test "/workspaces/lab1/build/bin/lab1_test")
set_tests_properties(lab1_test PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/lab1/tests/CMakeLists.txt;34;add_test;/workspaces/lab1/tests/CMakeLists.txt;0;")
add_test(lab2_test "/workspaces/lab1/build/bin/lab2_test")
set_tests_properties(lab2_test PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/lab1/tests/CMakeLists.txt;35;add_test;/workspaces/lab1/tests/CMakeLists.txt;0;")
add_test(lab3_test "/workspaces/lab1/build/bin/lab3_test")
set_tests_properties(lab3_test PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/lab1/tests/CMakeLists.txt;36;add_test;/workspaces/lab1/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
