# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = D:/SoftWare/Environment/Cmake/bin/cmake.exe

# The command to remove a file.
RM = D:/SoftWare/Environment/Cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build

# Include any dependencies generated for this target.
include CMakeFiles/MyPass_Pass.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyPass_Pass.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyPass_Pass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyPass_Pass.dir/flags.make

CMakeFiles/MyPass_Pass.dir/MyPass.obj: CMakeFiles/MyPass_Pass.dir/flags.make
CMakeFiles/MyPass_Pass.dir/MyPass.obj: D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/MyPass.cpp
CMakeFiles/MyPass_Pass.dir/MyPass.obj: CMakeFiles/MyPass_Pass.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyPass_Pass.dir/MyPass.obj"
	D:/SoftWare/Environment/C++/MinGW-w64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyPass_Pass.dir/MyPass.obj -MF CMakeFiles/MyPass_Pass.dir/MyPass.obj.d -o CMakeFiles/MyPass_Pass.dir/MyPass.obj -c D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/MyPass.cpp

CMakeFiles/MyPass_Pass.dir/MyPass.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyPass_Pass.dir/MyPass.i"
	D:/SoftWare/Environment/C++/MinGW-w64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/MyPass.cpp > CMakeFiles/MyPass_Pass.dir/MyPass.i

CMakeFiles/MyPass_Pass.dir/MyPass.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyPass_Pass.dir/MyPass.s"
	D:/SoftWare/Environment/C++/MinGW-w64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/MyPass.cpp -o CMakeFiles/MyPass_Pass.dir/MyPass.s

# Object files for target MyPass_Pass
MyPass_Pass_OBJECTS = \
"CMakeFiles/MyPass_Pass.dir/MyPass.obj"

# External object files for target MyPass_Pass
MyPass_Pass_EXTERNAL_OBJECTS =

libMyPass_Pass.dll: CMakeFiles/MyPass_Pass.dir/MyPass.obj
libMyPass_Pass.dll: CMakeFiles/MyPass_Pass.dir/build.make
libMyPass_Pass.dll: CMakeFiles/MyPass_Pass.dir/linkLibs.rsp
libMyPass_Pass.dll: CMakeFiles/MyPass_Pass.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libMyPass_Pass.dll"
	D:/SoftWare/Environment/Cmake/bin/cmake.exe -E rm -f CMakeFiles/MyPass_Pass.dir/objects.a
	D:/SoftWare/Environment/C++/MinGW-w64/mingw64/bin/ar.exe qc CMakeFiles/MyPass_Pass.dir/objects.a @CMakeFiles/MyPass_Pass.dir/objects1.rsp
	D:/SoftWare/Environment/C++/MinGW-w64/mingw64/bin/c++.exe -shared -o libMyPass_Pass.dll -Wl,--major-image-version,0,--minor-image-version,0 -Wl,--whole-archive CMakeFiles/MyPass_Pass.dir/objects.a -Wl,--no-whole-archive @CMakeFiles/MyPass_Pass.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/MyPass_Pass.dir/build: libMyPass_Pass.dll
.PHONY : CMakeFiles/MyPass_Pass.dir/build

CMakeFiles/MyPass_Pass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyPass_Pass.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyPass_Pass.dir/clean

CMakeFiles/MyPass_Pass.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build/CMakeFiles/MyPass_Pass.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyPass_Pass.dir/depend

