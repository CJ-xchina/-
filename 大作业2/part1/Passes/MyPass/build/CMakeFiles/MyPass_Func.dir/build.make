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
include CMakeFiles/MyPass_Func.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyPass_Func.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyPass_Func.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyPass_Func.dir/flags.make

CMakeFiles/MyPass_Func.dir/MyFunc.obj: CMakeFiles/MyPass_Func.dir/flags.make
CMakeFiles/MyPass_Func.dir/MyFunc.obj: D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/MyFunc.cpp
CMakeFiles/MyPass_Func.dir/MyFunc.obj: CMakeFiles/MyPass_Func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyPass_Func.dir/MyFunc.obj"
	D:/SoftWare/Environment/C++/MinGW-w64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyPass_Func.dir/MyFunc.obj -MF CMakeFiles/MyPass_Func.dir/MyFunc.obj.d -o CMakeFiles/MyPass_Func.dir/MyFunc.obj -c D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/MyFunc.cpp

CMakeFiles/MyPass_Func.dir/MyFunc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyPass_Func.dir/MyFunc.i"
	D:/SoftWare/Environment/C++/MinGW-w64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/MyFunc.cpp > CMakeFiles/MyPass_Func.dir/MyFunc.i

CMakeFiles/MyPass_Func.dir/MyFunc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyPass_Func.dir/MyFunc.s"
	D:/SoftWare/Environment/C++/MinGW-w64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/MyFunc.cpp -o CMakeFiles/MyPass_Func.dir/MyFunc.s

# Object files for target MyPass_Func
MyPass_Func_OBJECTS = \
"CMakeFiles/MyPass_Func.dir/MyFunc.obj"

# External object files for target MyPass_Func
MyPass_Func_EXTERNAL_OBJECTS =

libMyPass_Func.a: CMakeFiles/MyPass_Func.dir/MyFunc.obj
libMyPass_Func.a: CMakeFiles/MyPass_Func.dir/build.make
libMyPass_Func.a: CMakeFiles/MyPass_Func.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libMyPass_Func.a"
	$(CMAKE_COMMAND) -P CMakeFiles/MyPass_Func.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyPass_Func.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyPass_Func.dir/build: libMyPass_Func.a
.PHONY : CMakeFiles/MyPass_Func.dir/build

CMakeFiles/MyPass_Func.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyPass_Func.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyPass_Func.dir/clean

CMakeFiles/MyPass_Func.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build D:/MY_FILES/学习/资料/软件测试/大作业2/part1/Passes/MyPass/build/CMakeFiles/MyPass_Func.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyPass_Func.dir/depend

