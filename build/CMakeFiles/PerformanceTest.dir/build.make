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
include CMakeFiles/PerformanceTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PerformanceTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PerformanceTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PerformanceTest.dir/flags.make

CMakeFiles/PerformanceTest.dir/examples/examples.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/examples/examples.cpp.o: ../examples/examples.cpp
CMakeFiles/PerformanceTest.dir/examples/examples.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PerformanceTest.dir/examples/examples.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/examples/examples.cpp.o -MF CMakeFiles/PerformanceTest.dir/examples/examples.cpp.o.d -o CMakeFiles/PerformanceTest.dir/examples/examples.cpp.o -c /home/jiale001/VH-DSSE/examples/examples.cpp

CMakeFiles/PerformanceTest.dir/examples/examples.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/examples/examples.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/examples/examples.cpp > CMakeFiles/PerformanceTest.dir/examples/examples.cpp.i

CMakeFiles/PerformanceTest.dir/examples/examples.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/examples/examples.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/examples/examples.cpp -o CMakeFiles/PerformanceTest.dir/examples/examples.cpp.s

CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.o: ../examples/SearchTest.cpp
CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.o -MF CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.o.d -o CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.o -c /home/jiale001/VH-DSSE/examples/SearchTest.cpp

CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/examples/SearchTest.cpp > CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.i

CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/examples/SearchTest.cpp -o CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.s

CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.o: ../examples/UpdateTest.cpp
CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.o -MF CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.o.d -o CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.o -c /home/jiale001/VH-DSSE/examples/UpdateTest.cpp

CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/examples/UpdateTest.cpp > CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.i

CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/examples/UpdateTest.cpp -o CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.s

CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.o: ../examples/AccuracyTest.cpp
CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.o -MF CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.o.d -o CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.o -c /home/jiale001/VH-DSSE/examples/AccuracyTest.cpp

CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/examples/AccuracyTest.cpp > CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.i

CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/examples/AccuracyTest.cpp -o CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.s

CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.o: ../dynamic/Client.cpp
CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.o -MF CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.o.d -o CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.o -c /home/jiale001/VH-DSSE/dynamic/Client.cpp

CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/dynamic/Client.cpp > CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.i

CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/dynamic/Client.cpp -o CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.s

CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.o: ../dynamic/ClientHandler.cpp
CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.o -MF CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.o.d -o CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.o -c /home/jiale001/VH-DSSE/dynamic/ClientHandler.cpp

CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/dynamic/ClientHandler.cpp > CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.i

CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/dynamic/ClientHandler.cpp -o CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.s

CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.o: ../dynamic/Server.cpp
CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.o -MF CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.o.d -o CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.o -c /home/jiale001/VH-DSSE/dynamic/Server.cpp

CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/dynamic/Server.cpp > CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.i

CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/dynamic/Server.cpp -o CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.s

CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.o: ../kuku/cuckoo.cpp
CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.o -MF CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.o.d -o CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.o -c /home/jiale001/VH-DSSE/kuku/cuckoo.cpp

CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/kuku/cuckoo.cpp > CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.i

CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/kuku/cuckoo.cpp -o CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.s

CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.o: ../dPRF/GGMTree.cpp
CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.o -MF CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.o.d -o CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.o -c /home/jiale001/VH-DSSE/dPRF/GGMTree.cpp

CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/dPRF/GGMTree.cpp > CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.i

CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/dPRF/GGMTree.cpp -o CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.s

CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.o: CMakeFiles/PerformanceTest.dir/flags.make
CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.o: ../utils/Utils.cpp
CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.o: CMakeFiles/PerformanceTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.o -MF CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.o.d -o CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.o -c /home/jiale001/VH-DSSE/utils/Utils.cpp

CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jiale001/VH-DSSE/utils/Utils.cpp > CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.i

CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jiale001/VH-DSSE/utils/Utils.cpp -o CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.s

# Object files for target PerformanceTest
PerformanceTest_OBJECTS = \
"CMakeFiles/PerformanceTest.dir/examples/examples.cpp.o" \
"CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.o" \
"CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.o" \
"CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.o" \
"CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.o" \
"CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.o" \
"CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.o" \
"CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.o" \
"CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.o" \
"CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.o"

# External object files for target PerformanceTest
PerformanceTest_EXTERNAL_OBJECTS =

PerformanceTest: CMakeFiles/PerformanceTest.dir/examples/examples.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/examples/SearchTest.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/examples/UpdateTest.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/examples/AccuracyTest.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/dynamic/Client.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/dynamic/ClientHandler.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/dynamic/Server.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/kuku/cuckoo.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/dPRF/GGMTree.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/utils/Utils.cpp.o
PerformanceTest: CMakeFiles/PerformanceTest.dir/build.make
PerformanceTest: /usr/lib64/libcrypto.so
PerformanceTest: CMakeFiles/PerformanceTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jiale001/VH-DSSE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable PerformanceTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PerformanceTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PerformanceTest.dir/build: PerformanceTest
.PHONY : CMakeFiles/PerformanceTest.dir/build

CMakeFiles/PerformanceTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PerformanceTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PerformanceTest.dir/clean

CMakeFiles/PerformanceTest.dir/depend:
	cd /home/jiale001/VH-DSSE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jiale001/VH-DSSE /home/jiale001/VH-DSSE /home/jiale001/VH-DSSE/build /home/jiale001/VH-DSSE/build /home/jiale001/VH-DSSE/build/CMakeFiles/PerformanceTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PerformanceTest.dir/depend

