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

# Utility rule file for dist.

# Include any custom commands dependencies for this target.
include CMakeFiles/dist.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dist.dir/progress.make

CMakeFiles/dist: html
	cmake -E remove_directory lemon-1.3.1
	hg archive lemon-1.3.1
	cmake -E copy cmake/version.cmake lemon-1.3.1/cmake/version.cmake
	tar -czf lemon-nodoc-1.3.1.tar.gz lemon-1.3.1
	zip -r lemon-nodoc-1.3.1.zip lemon-1.3.1
	cmake -E copy_directory doc/html lemon-1.3.1/doc/html
	tar -czf lemon-1.3.1.tar.gz lemon-1.3.1
	zip -r lemon-1.3.1.zip lemon-1.3.1
	cmake -E copy_directory doc/html lemon-doc-1.3.1
	tar -czf lemon-doc-1.3.1.tar.gz lemon-doc-1.3.1
	zip -r lemon-doc-1.3.1.zip lemon-doc-1.3.1
	cmake -E remove_directory lemon-1.3.1
	cmake -E remove_directory lemon-doc-1.3.1

dist: CMakeFiles/dist
dist: CMakeFiles/dist.dir/build.make
.PHONY : dist

# Rule to build all files generated by this target.
CMakeFiles/dist.dir/build: dist
.PHONY : CMakeFiles/dist.dir/build

CMakeFiles/dist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dist.dir/clean

CMakeFiles/dist.dir/depend:
	cd /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1 /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1 /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1 /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1 /home/john/Documents/Projetos/mc859/mc859-2023-09-15/lemon/lemon-1.3.1/CMakeFiles/dist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dist.dir/depend

