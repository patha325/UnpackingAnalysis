# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/B2_Analysis.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/B2_Analysis.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/B2_Analysis.dir/flags.make

examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o: examples/CMakeFiles/B2_Analysis.dir/flags.make
examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o: ../examples/B2_rootAnalysis.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o"
	cd /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o -c /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/examples/B2_rootAnalysis.cpp

examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.i"
	cd /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/examples/B2_rootAnalysis.cpp > CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.i

examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.s"
	cd /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/examples/B2_rootAnalysis.cpp -o CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.s

examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o.requires:

.PHONY : examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o.requires

examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o.provides: examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/B2_Analysis.dir/build.make examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o.provides.build
.PHONY : examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o.provides

examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o.provides.build: examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o


# Object files for target B2_Analysis
B2_Analysis_OBJECTS = \
"CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o"

# External object files for target B2_Analysis
B2_Analysis_EXTERNAL_OBJECTS =

../bin/B2_Analysis: examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o
../bin/B2_Analysis: examples/CMakeFiles/B2_Analysis.dir/build.make
../bin/B2_Analysis: ../lib/libBabyMINDUnpack.dylib
../bin/B2_Analysis: examples/CMakeFiles/B2_Analysis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/B2_Analysis"
	cd /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/B2_Analysis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/B2_Analysis.dir/build: ../bin/B2_Analysis

.PHONY : examples/CMakeFiles/B2_Analysis.dir/build

examples/CMakeFiles/B2_Analysis.dir/requires: examples/CMakeFiles/B2_Analysis.dir/B2_rootAnalysis.cpp.o.requires

.PHONY : examples/CMakeFiles/B2_Analysis.dir/requires

examples/CMakeFiles/B2_Analysis.dir/clean:
	cd /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/B2_Analysis.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/B2_Analysis.dir/clean

examples/CMakeFiles/B2_Analysis.dir/depend:
	cd /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1 /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/examples /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build/examples /Users/jinaren/Documents/T2K/BabyMIND/J-PARC_physics_run/unpacking/Unpacking_3.1/build/examples/CMakeFiles/B2_Analysis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/B2_Analysis.dir/depend

