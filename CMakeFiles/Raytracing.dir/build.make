# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/ziagord/.local/lib/python3.11/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/ziagord/.local/lib/python3.11/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ziagord/dev/school/RayTracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ziagord/dev/school/RayTracer

# Include any dependencies generated for this target.
include CMakeFiles/Raytracing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Raytracing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Raytracing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Raytracing.dir/flags.make

CMakeFiles/Raytracing.dir/src/main.cpp.o: CMakeFiles/Raytracing.dir/flags.make
CMakeFiles/Raytracing.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/Raytracing.dir/src/main.cpp.o: CMakeFiles/Raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziagord/dev/school/RayTracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Raytracing.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Raytracing.dir/src/main.cpp.o -MF CMakeFiles/Raytracing.dir/src/main.cpp.o.d -o CMakeFiles/Raytracing.dir/src/main.cpp.o -c /home/ziagord/dev/school/RayTracer/src/main.cpp

CMakeFiles/Raytracing.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Raytracing.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziagord/dev/school/RayTracer/src/main.cpp > CMakeFiles/Raytracing.dir/src/main.cpp.i

CMakeFiles/Raytracing.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Raytracing.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziagord/dev/school/RayTracer/src/main.cpp -o CMakeFiles/Raytracing.dir/src/main.cpp.s

CMakeFiles/Raytracing.dir/src/Ray.cpp.o: CMakeFiles/Raytracing.dir/flags.make
CMakeFiles/Raytracing.dir/src/Ray.cpp.o: src/Ray.cpp
CMakeFiles/Raytracing.dir/src/Ray.cpp.o: CMakeFiles/Raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziagord/dev/school/RayTracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Raytracing.dir/src/Ray.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Raytracing.dir/src/Ray.cpp.o -MF CMakeFiles/Raytracing.dir/src/Ray.cpp.o.d -o CMakeFiles/Raytracing.dir/src/Ray.cpp.o -c /home/ziagord/dev/school/RayTracer/src/Ray.cpp

CMakeFiles/Raytracing.dir/src/Ray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Raytracing.dir/src/Ray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziagord/dev/school/RayTracer/src/Ray.cpp > CMakeFiles/Raytracing.dir/src/Ray.cpp.i

CMakeFiles/Raytracing.dir/src/Ray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Raytracing.dir/src/Ray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziagord/dev/school/RayTracer/src/Ray.cpp -o CMakeFiles/Raytracing.dir/src/Ray.cpp.s

CMakeFiles/Raytracing.dir/src/Camera.cpp.o: CMakeFiles/Raytracing.dir/flags.make
CMakeFiles/Raytracing.dir/src/Camera.cpp.o: src/Camera.cpp
CMakeFiles/Raytracing.dir/src/Camera.cpp.o: CMakeFiles/Raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziagord/dev/school/RayTracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Raytracing.dir/src/Camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Raytracing.dir/src/Camera.cpp.o -MF CMakeFiles/Raytracing.dir/src/Camera.cpp.o.d -o CMakeFiles/Raytracing.dir/src/Camera.cpp.o -c /home/ziagord/dev/school/RayTracer/src/Camera.cpp

CMakeFiles/Raytracing.dir/src/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Raytracing.dir/src/Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziagord/dev/school/RayTracer/src/Camera.cpp > CMakeFiles/Raytracing.dir/src/Camera.cpp.i

CMakeFiles/Raytracing.dir/src/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Raytracing.dir/src/Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziagord/dev/school/RayTracer/src/Camera.cpp -o CMakeFiles/Raytracing.dir/src/Camera.cpp.s

CMakeFiles/Raytracing.dir/src/Pixel.cpp.o: CMakeFiles/Raytracing.dir/flags.make
CMakeFiles/Raytracing.dir/src/Pixel.cpp.o: src/Pixel.cpp
CMakeFiles/Raytracing.dir/src/Pixel.cpp.o: CMakeFiles/Raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziagord/dev/school/RayTracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Raytracing.dir/src/Pixel.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Raytracing.dir/src/Pixel.cpp.o -MF CMakeFiles/Raytracing.dir/src/Pixel.cpp.o.d -o CMakeFiles/Raytracing.dir/src/Pixel.cpp.o -c /home/ziagord/dev/school/RayTracer/src/Pixel.cpp

CMakeFiles/Raytracing.dir/src/Pixel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Raytracing.dir/src/Pixel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziagord/dev/school/RayTracer/src/Pixel.cpp > CMakeFiles/Raytracing.dir/src/Pixel.cpp.i

CMakeFiles/Raytracing.dir/src/Pixel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Raytracing.dir/src/Pixel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziagord/dev/school/RayTracer/src/Pixel.cpp -o CMakeFiles/Raytracing.dir/src/Pixel.cpp.s

CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.o: CMakeFiles/Raytracing.dir/flags.make
CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.o: src/ColorDBL.cpp
CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.o: CMakeFiles/Raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziagord/dev/school/RayTracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.o -MF CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.o.d -o CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.o -c /home/ziagord/dev/school/RayTracer/src/ColorDBL.cpp

CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziagord/dev/school/RayTracer/src/ColorDBL.cpp > CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.i

CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziagord/dev/school/RayTracer/src/ColorDBL.cpp -o CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.s

CMakeFiles/Raytracing.dir/src/Triangle.cpp.o: CMakeFiles/Raytracing.dir/flags.make
CMakeFiles/Raytracing.dir/src/Triangle.cpp.o: src/Triangle.cpp
CMakeFiles/Raytracing.dir/src/Triangle.cpp.o: CMakeFiles/Raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziagord/dev/school/RayTracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Raytracing.dir/src/Triangle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Raytracing.dir/src/Triangle.cpp.o -MF CMakeFiles/Raytracing.dir/src/Triangle.cpp.o.d -o CMakeFiles/Raytracing.dir/src/Triangle.cpp.o -c /home/ziagord/dev/school/RayTracer/src/Triangle.cpp

CMakeFiles/Raytracing.dir/src/Triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Raytracing.dir/src/Triangle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziagord/dev/school/RayTracer/src/Triangle.cpp > CMakeFiles/Raytracing.dir/src/Triangle.cpp.i

CMakeFiles/Raytracing.dir/src/Triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Raytracing.dir/src/Triangle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziagord/dev/school/RayTracer/src/Triangle.cpp -o CMakeFiles/Raytracing.dir/src/Triangle.cpp.s

CMakeFiles/Raytracing.dir/src/LightSource.cpp.o: CMakeFiles/Raytracing.dir/flags.make
CMakeFiles/Raytracing.dir/src/LightSource.cpp.o: src/LightSource.cpp
CMakeFiles/Raytracing.dir/src/LightSource.cpp.o: CMakeFiles/Raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziagord/dev/school/RayTracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Raytracing.dir/src/LightSource.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Raytracing.dir/src/LightSource.cpp.o -MF CMakeFiles/Raytracing.dir/src/LightSource.cpp.o.d -o CMakeFiles/Raytracing.dir/src/LightSource.cpp.o -c /home/ziagord/dev/school/RayTracer/src/LightSource.cpp

CMakeFiles/Raytracing.dir/src/LightSource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Raytracing.dir/src/LightSource.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziagord/dev/school/RayTracer/src/LightSource.cpp > CMakeFiles/Raytracing.dir/src/LightSource.cpp.i

CMakeFiles/Raytracing.dir/src/LightSource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Raytracing.dir/src/LightSource.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziagord/dev/school/RayTracer/src/LightSource.cpp -o CMakeFiles/Raytracing.dir/src/LightSource.cpp.s

CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.o: CMakeFiles/Raytracing.dir/flags.make
CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.o: src/Tetrahedron.cpp
CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.o: CMakeFiles/Raytracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziagord/dev/school/RayTracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.o -MF CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.o.d -o CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.o -c /home/ziagord/dev/school/RayTracer/src/Tetrahedron.cpp

CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziagord/dev/school/RayTracer/src/Tetrahedron.cpp > CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.i

CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziagord/dev/school/RayTracer/src/Tetrahedron.cpp -o CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.s

# Object files for target Raytracing
Raytracing_OBJECTS = \
"CMakeFiles/Raytracing.dir/src/main.cpp.o" \
"CMakeFiles/Raytracing.dir/src/Ray.cpp.o" \
"CMakeFiles/Raytracing.dir/src/Camera.cpp.o" \
"CMakeFiles/Raytracing.dir/src/Pixel.cpp.o" \
"CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.o" \
"CMakeFiles/Raytracing.dir/src/Triangle.cpp.o" \
"CMakeFiles/Raytracing.dir/src/LightSource.cpp.o" \
"CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.o"

# External object files for target Raytracing
Raytracing_EXTERNAL_OBJECTS =

Raytracing: CMakeFiles/Raytracing.dir/src/main.cpp.o
Raytracing: CMakeFiles/Raytracing.dir/src/Ray.cpp.o
Raytracing: CMakeFiles/Raytracing.dir/src/Camera.cpp.o
Raytracing: CMakeFiles/Raytracing.dir/src/Pixel.cpp.o
Raytracing: CMakeFiles/Raytracing.dir/src/ColorDBL.cpp.o
Raytracing: CMakeFiles/Raytracing.dir/src/Triangle.cpp.o
Raytracing: CMakeFiles/Raytracing.dir/src/LightSource.cpp.o
Raytracing: CMakeFiles/Raytracing.dir/src/Tetrahedron.cpp.o
Raytracing: CMakeFiles/Raytracing.dir/build.make
Raytracing: CMakeFiles/Raytracing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ziagord/dev/school/RayTracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Raytracing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Raytracing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Raytracing.dir/build: Raytracing
.PHONY : CMakeFiles/Raytracing.dir/build

CMakeFiles/Raytracing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Raytracing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Raytracing.dir/clean

CMakeFiles/Raytracing.dir/depend:
	cd /home/ziagord/dev/school/RayTracer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ziagord/dev/school/RayTracer /home/ziagord/dev/school/RayTracer /home/ziagord/dev/school/RayTracer /home/ziagord/dev/school/RayTracer /home/ziagord/dev/school/RayTracer/CMakeFiles/Raytracing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Raytracing.dir/depend

