# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "F:\CLion 2020.1.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "F:\CLion 2020.1.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\externalsort

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\externalsort\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/externalsort.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/externalsort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/externalsort.dir/flags.make

CMakeFiles/externalsort.dir/main.cpp.obj: CMakeFiles/externalsort.dir/flags.make
CMakeFiles/externalsort.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\externalsort\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/externalsort.dir/main.cpp.obj"
	F:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\externalsort.dir\main.cpp.obj -c F:\externalsort\main.cpp

CMakeFiles/externalsort.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/externalsort.dir/main.cpp.i"
	F:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\externalsort\main.cpp > CMakeFiles\externalsort.dir\main.cpp.i

CMakeFiles/externalsort.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/externalsort.dir/main.cpp.s"
	F:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\externalsort\main.cpp -o CMakeFiles\externalsort.dir\main.cpp.s

CMakeFiles/externalsort.dir/functions.cpp.obj: CMakeFiles/externalsort.dir/flags.make
CMakeFiles/externalsort.dir/functions.cpp.obj: ../functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\externalsort\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/externalsort.dir/functions.cpp.obj"
	F:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\externalsort.dir\functions.cpp.obj -c F:\externalsort\functions.cpp

CMakeFiles/externalsort.dir/functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/externalsort.dir/functions.cpp.i"
	F:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\externalsort\functions.cpp > CMakeFiles\externalsort.dir\functions.cpp.i

CMakeFiles/externalsort.dir/functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/externalsort.dir/functions.cpp.s"
	F:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\externalsort\functions.cpp -o CMakeFiles\externalsort.dir\functions.cpp.s

# Object files for target externalsort
externalsort_OBJECTS = \
"CMakeFiles/externalsort.dir/main.cpp.obj" \
"CMakeFiles/externalsort.dir/functions.cpp.obj"

# External object files for target externalsort
externalsort_EXTERNAL_OBJECTS =

externalsort.exe: CMakeFiles/externalsort.dir/main.cpp.obj
externalsort.exe: CMakeFiles/externalsort.dir/functions.cpp.obj
externalsort.exe: CMakeFiles/externalsort.dir/build.make
externalsort.exe: CMakeFiles/externalsort.dir/linklibs.rsp
externalsort.exe: CMakeFiles/externalsort.dir/objects1.rsp
externalsort.exe: CMakeFiles/externalsort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\externalsort\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable externalsort.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\externalsort.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/externalsort.dir/build: externalsort.exe

.PHONY : CMakeFiles/externalsort.dir/build

CMakeFiles/externalsort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\externalsort.dir\cmake_clean.cmake
.PHONY : CMakeFiles/externalsort.dir/clean

CMakeFiles/externalsort.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\externalsort F:\externalsort F:\externalsort\cmake-build-debug F:\externalsort\cmake-build-debug F:\externalsort\cmake-build-debug\CMakeFiles\externalsort.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/externalsort.dir/depend
