# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jaehoonhyun/workspace/lockfree_queue_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaehoonhyun/workspace/lockfree_queue_project/build

# Include any dependencies generated for this target.
include CMakeFiles/template_project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/template_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/template_project.dir/flags.make

CMakeFiles/template_project.dir/src/epoll-client.cc.o: CMakeFiles/template_project.dir/flags.make
CMakeFiles/template_project.dir/src/epoll-client.cc.o: ../src/epoll-client.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaehoonhyun/workspace/lockfree_queue_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/template_project.dir/src/epoll-client.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/template_project.dir/src/epoll-client.cc.o -c /home/jaehoonhyun/workspace/lockfree_queue_project/src/epoll-client.cc

CMakeFiles/template_project.dir/src/epoll-client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template_project.dir/src/epoll-client.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaehoonhyun/workspace/lockfree_queue_project/src/epoll-client.cc > CMakeFiles/template_project.dir/src/epoll-client.cc.i

CMakeFiles/template_project.dir/src/epoll-client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template_project.dir/src/epoll-client.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaehoonhyun/workspace/lockfree_queue_project/src/epoll-client.cc -o CMakeFiles/template_project.dir/src/epoll-client.cc.s

CMakeFiles/template_project.dir/src/epoll-client.cc.o.requires:

.PHONY : CMakeFiles/template_project.dir/src/epoll-client.cc.o.requires

CMakeFiles/template_project.dir/src/epoll-client.cc.o.provides: CMakeFiles/template_project.dir/src/epoll-client.cc.o.requires
	$(MAKE) -f CMakeFiles/template_project.dir/build.make CMakeFiles/template_project.dir/src/epoll-client.cc.o.provides.build
.PHONY : CMakeFiles/template_project.dir/src/epoll-client.cc.o.provides

CMakeFiles/template_project.dir/src/epoll-client.cc.o.provides.build: CMakeFiles/template_project.dir/src/epoll-client.cc.o


CMakeFiles/template_project.dir/src/epoll-server.cc.o: CMakeFiles/template_project.dir/flags.make
CMakeFiles/template_project.dir/src/epoll-server.cc.o: ../src/epoll-server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaehoonhyun/workspace/lockfree_queue_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/template_project.dir/src/epoll-server.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/template_project.dir/src/epoll-server.cc.o -c /home/jaehoonhyun/workspace/lockfree_queue_project/src/epoll-server.cc

CMakeFiles/template_project.dir/src/epoll-server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template_project.dir/src/epoll-server.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaehoonhyun/workspace/lockfree_queue_project/src/epoll-server.cc > CMakeFiles/template_project.dir/src/epoll-server.cc.i

CMakeFiles/template_project.dir/src/epoll-server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template_project.dir/src/epoll-server.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaehoonhyun/workspace/lockfree_queue_project/src/epoll-server.cc -o CMakeFiles/template_project.dir/src/epoll-server.cc.s

CMakeFiles/template_project.dir/src/epoll-server.cc.o.requires:

.PHONY : CMakeFiles/template_project.dir/src/epoll-server.cc.o.requires

CMakeFiles/template_project.dir/src/epoll-server.cc.o.provides: CMakeFiles/template_project.dir/src/epoll-server.cc.o.requires
	$(MAKE) -f CMakeFiles/template_project.dir/build.make CMakeFiles/template_project.dir/src/epoll-server.cc.o.provides.build
.PHONY : CMakeFiles/template_project.dir/src/epoll-server.cc.o.provides

CMakeFiles/template_project.dir/src/epoll-server.cc.o.provides.build: CMakeFiles/template_project.dir/src/epoll-server.cc.o


CMakeFiles/template_project.dir/src/utils.cc.o: CMakeFiles/template_project.dir/flags.make
CMakeFiles/template_project.dir/src/utils.cc.o: ../src/utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaehoonhyun/workspace/lockfree_queue_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/template_project.dir/src/utils.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/template_project.dir/src/utils.cc.o -c /home/jaehoonhyun/workspace/lockfree_queue_project/src/utils.cc

CMakeFiles/template_project.dir/src/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template_project.dir/src/utils.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaehoonhyun/workspace/lockfree_queue_project/src/utils.cc > CMakeFiles/template_project.dir/src/utils.cc.i

CMakeFiles/template_project.dir/src/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template_project.dir/src/utils.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaehoonhyun/workspace/lockfree_queue_project/src/utils.cc -o CMakeFiles/template_project.dir/src/utils.cc.s

CMakeFiles/template_project.dir/src/utils.cc.o.requires:

.PHONY : CMakeFiles/template_project.dir/src/utils.cc.o.requires

CMakeFiles/template_project.dir/src/utils.cc.o.provides: CMakeFiles/template_project.dir/src/utils.cc.o.requires
	$(MAKE) -f CMakeFiles/template_project.dir/build.make CMakeFiles/template_project.dir/src/utils.cc.o.provides.build
.PHONY : CMakeFiles/template_project.dir/src/utils.cc.o.provides

CMakeFiles/template_project.dir/src/utils.cc.o.provides.build: CMakeFiles/template_project.dir/src/utils.cc.o


CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o: CMakeFiles/template_project.dir/flags.make
CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o: ../gtest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaehoonhyun/workspace/lockfree_queue_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o -c /home/jaehoonhyun/workspace/lockfree_queue_project/gtest/src/gtest-all.cc

CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaehoonhyun/workspace/lockfree_queue_project/gtest/src/gtest-all.cc > CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.i

CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaehoonhyun/workspace/lockfree_queue_project/gtest/src/gtest-all.cc -o CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.s

CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o.requires:

.PHONY : CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o.requires

CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o.provides: CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o.requires
	$(MAKE) -f CMakeFiles/template_project.dir/build.make CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o.provides.build
.PHONY : CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o.provides

CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o.provides.build: CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o


CMakeFiles/template_project.dir/main.cpp.o: CMakeFiles/template_project.dir/flags.make
CMakeFiles/template_project.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaehoonhyun/workspace/lockfree_queue_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/template_project.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/template_project.dir/main.cpp.o -c /home/jaehoonhyun/workspace/lockfree_queue_project/main.cpp

CMakeFiles/template_project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template_project.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaehoonhyun/workspace/lockfree_queue_project/main.cpp > CMakeFiles/template_project.dir/main.cpp.i

CMakeFiles/template_project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template_project.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaehoonhyun/workspace/lockfree_queue_project/main.cpp -o CMakeFiles/template_project.dir/main.cpp.s

CMakeFiles/template_project.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/template_project.dir/main.cpp.o.requires

CMakeFiles/template_project.dir/main.cpp.o.provides: CMakeFiles/template_project.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/template_project.dir/build.make CMakeFiles/template_project.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/template_project.dir/main.cpp.o.provides

CMakeFiles/template_project.dir/main.cpp.o.provides.build: CMakeFiles/template_project.dir/main.cpp.o


# Object files for target template_project
template_project_OBJECTS = \
"CMakeFiles/template_project.dir/src/epoll-client.cc.o" \
"CMakeFiles/template_project.dir/src/epoll-server.cc.o" \
"CMakeFiles/template_project.dir/src/utils.cc.o" \
"CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o" \
"CMakeFiles/template_project.dir/main.cpp.o"

# External object files for target template_project
template_project_EXTERNAL_OBJECTS =

template_project: CMakeFiles/template_project.dir/src/epoll-client.cc.o
template_project: CMakeFiles/template_project.dir/src/epoll-server.cc.o
template_project: CMakeFiles/template_project.dir/src/utils.cc.o
template_project: CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o
template_project: CMakeFiles/template_project.dir/main.cpp.o
template_project: CMakeFiles/template_project.dir/build.make
template_project: CMakeFiles/template_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaehoonhyun/workspace/lockfree_queue_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable template_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/template_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/template_project.dir/build: template_project

.PHONY : CMakeFiles/template_project.dir/build

CMakeFiles/template_project.dir/requires: CMakeFiles/template_project.dir/src/epoll-client.cc.o.requires
CMakeFiles/template_project.dir/requires: CMakeFiles/template_project.dir/src/epoll-server.cc.o.requires
CMakeFiles/template_project.dir/requires: CMakeFiles/template_project.dir/src/utils.cc.o.requires
CMakeFiles/template_project.dir/requires: CMakeFiles/template_project.dir/gtest/src/gtest-all.cc.o.requires
CMakeFiles/template_project.dir/requires: CMakeFiles/template_project.dir/main.cpp.o.requires

.PHONY : CMakeFiles/template_project.dir/requires

CMakeFiles/template_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/template_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/template_project.dir/clean

CMakeFiles/template_project.dir/depend:
	cd /home/jaehoonhyun/workspace/lockfree_queue_project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaehoonhyun/workspace/lockfree_queue_project /home/jaehoonhyun/workspace/lockfree_queue_project /home/jaehoonhyun/workspace/lockfree_queue_project/build /home/jaehoonhyun/workspace/lockfree_queue_project/build /home/jaehoonhyun/workspace/lockfree_queue_project/build/CMakeFiles/template_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/template_project.dir/depend

