# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1

# Include any dependencies generated for this target.
include test/CMakeFiles/time_measure_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/time_measure_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/time_measure_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/time_measure_test.dir/flags.make

test/CMakeFiles/time_measure_test.dir/time_measure_test.cc.o: test/CMakeFiles/time_measure_test.dir/flags.make
test/CMakeFiles/time_measure_test.dir/time_measure_test.cc.o: test/time_measure_test.cc
test/CMakeFiles/time_measure_test.dir/time_measure_test.cc.o: test/CMakeFiles/time_measure_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/time_measure_test.dir/time_measure_test.cc.o"
	cd /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/time_measure_test.dir/time_measure_test.cc.o -MF CMakeFiles/time_measure_test.dir/time_measure_test.cc.o.d -o CMakeFiles/time_measure_test.dir/time_measure_test.cc.o -c /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test/time_measure_test.cc

test/CMakeFiles/time_measure_test.dir/time_measure_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/time_measure_test.dir/time_measure_test.cc.i"
	cd /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test/time_measure_test.cc > CMakeFiles/time_measure_test.dir/time_measure_test.cc.i

test/CMakeFiles/time_measure_test.dir/time_measure_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/time_measure_test.dir/time_measure_test.cc.s"
	cd /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test/time_measure_test.cc -o CMakeFiles/time_measure_test.dir/time_measure_test.cc.s

# Object files for target time_measure_test
time_measure_test_OBJECTS = \
"CMakeFiles/time_measure_test.dir/time_measure_test.cc.o"

# External object files for target time_measure_test
time_measure_test_EXTERNAL_OBJECTS =

test/time_measure_test: test/CMakeFiles/time_measure_test.dir/time_measure_test.cc.o
test/time_measure_test: test/CMakeFiles/time_measure_test.dir/build.make
test/time_measure_test: lemon/libemon.a
test/time_measure_test: test/CMakeFiles/time_measure_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable time_measure_test"
	cd /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/time_measure_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/time_measure_test.dir/build: test/time_measure_test
.PHONY : test/CMakeFiles/time_measure_test.dir/build

test/CMakeFiles/time_measure_test.dir/clean:
	cd /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test && $(CMAKE_COMMAND) -P CMakeFiles/time_measure_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/time_measure_test.dir/clean

test/CMakeFiles/time_measure_test.dir/depend:
	cd /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1 /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1 /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/test/CMakeFiles/time_measure_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/time_measure_test.dir/depend

