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
CMAKE_SOURCE_DIR = /home/henrik/Documents/liu/tdp005/spel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/henrik/Documents/liu/tdp005/spel

# Include any dependencies generated for this target.
include CMakeFiles/sfml.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sfml.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sfml.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sfml.dir/flags.make

CMakeFiles/sfml.dir/game.cc.o: CMakeFiles/sfml.dir/flags.make
CMakeFiles/sfml.dir/game.cc.o: game.cc
CMakeFiles/sfml.dir/game.cc.o: CMakeFiles/sfml.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/henrik/Documents/liu/tdp005/spel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sfml.dir/game.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sfml.dir/game.cc.o -MF CMakeFiles/sfml.dir/game.cc.o.d -o CMakeFiles/sfml.dir/game.cc.o -c /home/henrik/Documents/liu/tdp005/spel/game.cc

CMakeFiles/sfml.dir/game.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml.dir/game.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/henrik/Documents/liu/tdp005/spel/game.cc > CMakeFiles/sfml.dir/game.cc.i

CMakeFiles/sfml.dir/game.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml.dir/game.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/henrik/Documents/liu/tdp005/spel/game.cc -o CMakeFiles/sfml.dir/game.cc.s

CMakeFiles/sfml.dir/world.cc.o: CMakeFiles/sfml.dir/flags.make
CMakeFiles/sfml.dir/world.cc.o: world.cc
CMakeFiles/sfml.dir/world.cc.o: CMakeFiles/sfml.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/henrik/Documents/liu/tdp005/spel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sfml.dir/world.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sfml.dir/world.cc.o -MF CMakeFiles/sfml.dir/world.cc.o.d -o CMakeFiles/sfml.dir/world.cc.o -c /home/henrik/Documents/liu/tdp005/spel/world.cc

CMakeFiles/sfml.dir/world.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml.dir/world.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/henrik/Documents/liu/tdp005/spel/world.cc > CMakeFiles/sfml.dir/world.cc.i

CMakeFiles/sfml.dir/world.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml.dir/world.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/henrik/Documents/liu/tdp005/spel/world.cc -o CMakeFiles/sfml.dir/world.cc.s

# Object files for target sfml
sfml_OBJECTS = \
"CMakeFiles/sfml.dir/game.cc.o" \
"CMakeFiles/sfml.dir/world.cc.o"

# External object files for target sfml
sfml_EXTERNAL_OBJECTS =

sfml: CMakeFiles/sfml.dir/game.cc.o
sfml: CMakeFiles/sfml.dir/world.cc.o
sfml: CMakeFiles/sfml.dir/build.make
sfml: /usr/lib/x86_64-linux-gnu/libsfml-network.so.2.5.1
sfml: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
sfml: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
sfml: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
sfml: CMakeFiles/sfml.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/henrik/Documents/liu/tdp005/spel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable sfml"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sfml.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sfml.dir/build: sfml
.PHONY : CMakeFiles/sfml.dir/build

CMakeFiles/sfml.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sfml.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sfml.dir/clean

CMakeFiles/sfml.dir/depend:
	cd /home/henrik/Documents/liu/tdp005/spel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/henrik/Documents/liu/tdp005/spel /home/henrik/Documents/liu/tdp005/spel /home/henrik/Documents/liu/tdp005/spel /home/henrik/Documents/liu/tdp005/spel /home/henrik/Documents/liu/tdp005/spel/CMakeFiles/sfml.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sfml.dir/depend

