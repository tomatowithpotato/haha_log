# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/lighthouse/MyCode/haha_log

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lighthouse/MyCode/haha_log/build

# Include any dependencies generated for this target.
include CMakeFiles/SyncLogTest.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SyncLogTest.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SyncLogTest.out.dir/flags.make

CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.o: CMakeFiles/SyncLogTest.out.dir/flags.make
CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.o: ../tests/SyncLogTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lighthouse/MyCode/haha_log/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.o -c /home/lighthouse/MyCode/haha_log/tests/SyncLogTest.cc

CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lighthouse/MyCode/haha_log/tests/SyncLogTest.cc > CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.i

CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lighthouse/MyCode/haha_log/tests/SyncLogTest.cc -o CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.s

# Object files for target SyncLogTest.out
SyncLogTest_out_OBJECTS = \
"CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.o"

# External object files for target SyncLogTest.out
SyncLogTest_out_EXTERNAL_OBJECTS =

../bin/debug/SyncLogTest.out: CMakeFiles/SyncLogTest.out.dir/tests/SyncLogTest.cc.o
../bin/debug/SyncLogTest.out: CMakeFiles/SyncLogTest.out.dir/build.make
../bin/debug/SyncLogTest.out: ../lib/debug/libhaha_log.so
../bin/debug/SyncLogTest.out: CMakeFiles/SyncLogTest.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lighthouse/MyCode/haha_log/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/debug/SyncLogTest.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SyncLogTest.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SyncLogTest.out.dir/build: ../bin/debug/SyncLogTest.out

.PHONY : CMakeFiles/SyncLogTest.out.dir/build

CMakeFiles/SyncLogTest.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SyncLogTest.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SyncLogTest.out.dir/clean

CMakeFiles/SyncLogTest.out.dir/depend:
	cd /home/lighthouse/MyCode/haha_log/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lighthouse/MyCode/haha_log /home/lighthouse/MyCode/haha_log /home/lighthouse/MyCode/haha_log/build /home/lighthouse/MyCode/haha_log/build /home/lighthouse/MyCode/haha_log/build/CMakeFiles/SyncLogTest.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SyncLogTest.out.dir/depend
