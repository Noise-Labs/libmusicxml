# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_SOURCE_DIR = /Users/menu/libmusicxml-git/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/menu/libmusicxml-git/build

# Include any dependencies generated for this target.
include CMakeFiles/meiread.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/meiread.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/meiread.dir/flags.make

CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.o: CMakeFiles/meiread.dir/flags.make
CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.o: /Users/menu/libmusicxml-git/samples/meiread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/menu/libmusicxml-git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.o -c /Users/menu/libmusicxml-git/samples/meiread.cpp

CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/menu/libmusicxml-git/samples/meiread.cpp > CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.i

CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/menu/libmusicxml-git/samples/meiread.cpp -o CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.s

# Object files for target meiread
meiread_OBJECTS = \
"CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.o"

# External object files for target meiread
meiread_EXTERNAL_OBJECTS =

bin/meiread: CMakeFiles/meiread.dir/Users/menu/libmusicxml-git/samples/meiread.o
bin/meiread: CMakeFiles/meiread.dir/build.make
bin/meiread: lib/libmusicxml2.a
bin/meiread: CMakeFiles/meiread.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/menu/libmusicxml-git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/meiread"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/meiread.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/meiread.dir/build: bin/meiread

.PHONY : CMakeFiles/meiread.dir/build

CMakeFiles/meiread.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/meiread.dir/cmake_clean.cmake
.PHONY : CMakeFiles/meiread.dir/clean

CMakeFiles/meiread.dir/depend:
	cd /Users/menu/libmusicxml-git/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/menu/libmusicxml-git/build /Users/menu/libmusicxml-git/build /Users/menu/libmusicxml-git/build /Users/menu/libmusicxml-git/build /Users/menu/libmusicxml-git/build/CMakeFiles/meiread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/meiread.dir/depend
