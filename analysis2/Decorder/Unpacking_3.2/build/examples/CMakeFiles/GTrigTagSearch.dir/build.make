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
include examples/CMakeFiles/GTrigTagSearch.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/GTrigTagSearch.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/GTrigTagSearch.dir/flags.make

examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o: examples/CMakeFiles/GTrigTagSearch.dir/flags.make
examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o: ../examples/GTrigTagSearch.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/analysis2/Decorder/Unpacking_3.2/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o"
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o -c /root/analysis2/Decorder/Unpacking_3.2/examples/GTrigTagSearch.cpp

examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.i"
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/analysis2/Decorder/Unpacking_3.2/examples/GTrigTagSearch.cpp > CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.i

examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.s"
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/analysis2/Decorder/Unpacking_3.2/examples/GTrigTagSearch.cpp -o CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.s

examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o.requires:
.PHONY : examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o.requires

examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o.provides: examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/GTrigTagSearch.dir/build.make examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o.provides.build
.PHONY : examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o.provides

examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o.provides.build: examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o

# Object files for target GTrigTagSearch
GTrigTagSearch_OBJECTS = \
"CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o"

# External object files for target GTrigTagSearch
GTrigTagSearch_EXTERNAL_OBJECTS =

../bin/GTrigTagSearch: examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o
../bin/GTrigTagSearch: examples/CMakeFiles/GTrigTagSearch.dir/build.make
../bin/GTrigTagSearch: ../lib/libBabyMINDUnpack.so
../bin/GTrigTagSearch: examples/CMakeFiles/GTrigTagSearch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/GTrigTagSearch"
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GTrigTagSearch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/GTrigTagSearch.dir/build: ../bin/GTrigTagSearch
.PHONY : examples/CMakeFiles/GTrigTagSearch.dir/build

examples/CMakeFiles/GTrigTagSearch.dir/requires: examples/CMakeFiles/GTrigTagSearch.dir/GTrigTagSearch.cpp.o.requires
.PHONY : examples/CMakeFiles/GTrigTagSearch.dir/requires

examples/CMakeFiles/GTrigTagSearch.dir/clean:
	cd /root/analysis2/Decorder/Unpacking_3.2/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/GTrigTagSearch.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/GTrigTagSearch.dir/clean

examples/CMakeFiles/GTrigTagSearch.dir/depend:
	cd /root/analysis2/Decorder/Unpacking_3.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/analysis2/Decorder/Unpacking_3.2 /root/analysis2/Decorder/Unpacking_3.2/examples /root/analysis2/Decorder/Unpacking_3.2/build /root/analysis2/Decorder/Unpacking_3.2/build/examples /root/analysis2/Decorder/Unpacking_3.2/build/examples/CMakeFiles/GTrigTagSearch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/GTrigTagSearch.dir/depend
