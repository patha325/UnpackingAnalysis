# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /root/analysis2/Decorder/Unpacking_3.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/analysis2/Decorder/Unpacking_3.2/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/dump.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/dump.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/dump.dir/flags.make

examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o: examples/CMakeFiles/dump.dir/flags.make
examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o: ../examples/babyMindDataDump.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/analysis2/Decorder/Unpacking_3.2/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o"
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/dump.dir/babyMindDataDump.cpp.o -c /root/analysis2/Decorder/Unpacking_3.2/examples/babyMindDataDump.cpp

examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dump.dir/babyMindDataDump.cpp.i"
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/analysis2/Decorder/Unpacking_3.2/examples/babyMindDataDump.cpp > CMakeFiles/dump.dir/babyMindDataDump.cpp.i

examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dump.dir/babyMindDataDump.cpp.s"
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/analysis2/Decorder/Unpacking_3.2/examples/babyMindDataDump.cpp -o CMakeFiles/dump.dir/babyMindDataDump.cpp.s

examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o.requires:
.PHONY : examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o.requires

examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o.provides: examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/dump.dir/build.make examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o.provides.build
.PHONY : examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o.provides

examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o.provides.build: examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o

# Object files for target dump
dump_OBJECTS = \
"CMakeFiles/dump.dir/babyMindDataDump.cpp.o"

# External object files for target dump
dump_EXTERNAL_OBJECTS =

../bin/dump: examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o
../bin/dump: examples/CMakeFiles/dump.dir/build.make
../bin/dump: ../lib/libBabyMINDUnpack.so
../bin/dump: examples/CMakeFiles/dump.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/dump"
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dump.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/dump.dir/build: ../bin/dump
.PHONY : examples/CMakeFiles/dump.dir/build

examples/CMakeFiles/dump.dir/requires: examples/CMakeFiles/dump.dir/babyMindDataDump.cpp.o.requires
.PHONY : examples/CMakeFiles/dump.dir/requires

examples/CMakeFiles/dump.dir/clean:
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/dump.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/dump.dir/clean

examples/CMakeFiles/dump.dir/depend:
	cd /root/analysis2/Decorder/Unpacking_3.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/analysis2/Decorder/Unpacking_3.2 /root/analysis2/Decorder/Unpacking_3.2/examples /root/analysis2/Decorder/Unpacking_3.2/build /root/analysis2/Decorder/Unpacking_3.2/build/examples /root/analysis2/Decorder/Unpacking_3.2/build/examples/CMakeFiles/dump.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/dump.dir/depend

