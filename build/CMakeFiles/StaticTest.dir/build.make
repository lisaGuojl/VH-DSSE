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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jiale001/VH-DSSE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jiale001/VH-DSSE/build

# Include any dependencies generated for this target.
include CMakeFiles/StaticTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/StaticTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/StaticTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StaticTest.dir/flags.make

CMakeFiles/StaticTest.dir/static/Source.cpp.o: CMakeFiles/StaticTest.dir/flags.make
CMakeFiles/StaticTest.dir/static/Source.cpp.o: ../static/Source.cpp
CMakeFiles/StaticTest.dir/static/Source.cpp.o: CMakeFiles/StaticTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StaticTest.dir/static/Source.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StaticTest.dir/static/Source.cpp.o -MF CMakeFiles/StaticTest.dir/static/Source.cpp.o.d -o CMakeFiles/StaticTest.dir/static/Source.cpp.o -c /home/jiale001/VH-DSSE/static/Source.cpp

CMakeFiles/StaticTest.dir/static/Source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StaticTest.dir/static/Source.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/static/Source.cpp > CMakeFiles/StaticTest.dir/static/Source.cpp.i

CMakeFiles/StaticTest.dir/static/Source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StaticTest.dir/static/Source.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/static/Source.cpp -o CMakeFiles/StaticTest.dir/static/Source.cpp.s

CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.o: CMakeFiles/StaticTest.dir/flags.make
CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.o: ../static/ClientHandler.cpp
CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.o: CMakeFiles/StaticTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.o -MF CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.o.d -o CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.o -c /home/jiale001/VH-DSSE/static/ClientHandler.cpp

CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/static/ClientHandler.cpp > CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.i

CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/static/ClientHandler.cpp -o CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.s

CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.o: CMakeFiles/StaticTest.dir/flags.make
CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.o: ../static/ServerHandler.cpp
CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.o: CMakeFiles/StaticTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.o -MF CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.o.d -o CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.o -c /home/jiale001/VH-DSSE/static/ServerHandler.cpp

CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/static/ServerHandler.cpp > CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.i

CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/static/ServerHandler.cpp -o CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.s

CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.o: CMakeFiles/StaticTest.dir/flags.make
CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.o: ../kuku/cuckoo.cpp
CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.o: CMakeFiles/StaticTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.o -MF CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.o.d -o CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.o -c /home/jiale001/VH-DSSE/kuku/cuckoo.cpp

CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/kuku/cuckoo.cpp > CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.i

CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/kuku/cuckoo.cpp -o CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.s

CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.o: CMakeFiles/StaticTest.dir/flags.make
CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.o: ../dPRF/GGMTree.cpp
CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.o: CMakeFiles/StaticTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.o -MF CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.o.d -o CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.o -c /home/jiale001/VH-DSSE/dPRF/GGMTree.cpp

CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/dPRF/GGMTree.cpp > CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.i

CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/dPRF/GGMTree.cpp -o CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.s

CMakeFiles/StaticTest.dir/utils/Utils.cpp.o: CMakeFiles/StaticTest.dir/flags.make
CMakeFiles/StaticTest.dir/utils/Utils.cpp.o: ../utils/Utils.cpp
CMakeFiles/StaticTest.dir/utils/Utils.cpp.o: CMakeFiles/StaticTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/StaticTest.dir/utils/Utils.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StaticTest.dir/utils/Utils.cpp.o -MF CMakeFiles/StaticTest.dir/utils/Utils.cpp.o.d -o CMakeFiles/StaticTest.dir/utils/Utils.cpp.o -c /home/jiale001/VH-DSSE/utils/Utils.cpp

CMakeFiles/StaticTest.dir/utils/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StaticTest.dir/utils/Utils.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/utils/Utils.cpp > CMakeFiles/StaticTest.dir/utils/Utils.cpp.i

CMakeFiles/StaticTest.dir/utils/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StaticTest.dir/utils/Utils.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/utils/Utils.cpp -o CMakeFiles/StaticTest.dir/utils/Utils.cpp.s

# Object files for target StaticTest
StaticTest_OBJECTS = \
"CMakeFiles/StaticTest.dir/static/Source.cpp.o" \
"CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.o" \
"CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.o" \
"CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.o" \
"CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.o" \
"CMakeFiles/StaticTest.dir/utils/Utils.cpp.o"

# External object files for target StaticTest
StaticTest_EXTERNAL_OBJECTS =

StaticTest: CMakeFiles/StaticTest.dir/static/Source.cpp.o
StaticTest: CMakeFiles/StaticTest.dir/static/ClientHandler.cpp.o
StaticTest: CMakeFiles/StaticTest.dir/static/ServerHandler.cpp.o
StaticTest: CMakeFiles/StaticTest.dir/kuku/cuckoo.cpp.o
StaticTest: CMakeFiles/StaticTest.dir/dPRF/GGMTree.cpp.o
StaticTest: CMakeFiles/StaticTest.dir/utils/Utils.cpp.o
StaticTest: CMakeFiles/StaticTest.dir/build.make
StaticTest: /usr/lib64/libcrypto.so
StaticTest: CMakeFiles/StaticTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable StaticTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StaticTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StaticTest.dir/build: StaticTest
.PHONY : CMakeFiles/StaticTest.dir/build

CMakeFiles/StaticTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StaticTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StaticTest.dir/clean

CMakeFiles/StaticTest.dir/depend:
	cd /home/jiale001/VH-DSSE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jiale001/VH-DSSE /home/jiale001/VH-DSSE /home/jiale001/VH-DSSE/build /home/jiale001/VH-DSSE/build /home/jiale001/VH-DSSE/build/CMakeFiles/StaticTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StaticTest.dir/depend

