# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mzy/Code/ChatServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mzy/Code/ChatServer/build

# Include any dependencies generated for this target.
include src/server/CMakeFiles/ChatServer.dir/depend.make

# Include the progress variables for this target.
include src/server/CMakeFiles/ChatServer.dir/progress.make

# Include the compile flags for this target's objects.
include src/server/CMakeFiles/ChatServer.dir/flags.make

src/server/CMakeFiles/ChatServer.dir/ChatServer.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/ChatServer.cc.o: ../src/server/ChatServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/server/CMakeFiles/ChatServer.dir/ChatServer.cc.o"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ChatServer.dir/ChatServer.cc.o -c /home/mzy/Code/ChatServer/src/server/ChatServer.cc

src/server/CMakeFiles/ChatServer.dir/ChatServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/ChatServer.cc.i"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/ChatServer/src/server/ChatServer.cc > CMakeFiles/ChatServer.dir/ChatServer.cc.i

src/server/CMakeFiles/ChatServer.dir/ChatServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/ChatServer.cc.s"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/ChatServer/src/server/ChatServer.cc -o CMakeFiles/ChatServer.dir/ChatServer.cc.s

src/server/CMakeFiles/ChatServer.dir/ChatService.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/ChatService.cc.o: ../src/server/ChatService.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/server/CMakeFiles/ChatServer.dir/ChatService.cc.o"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ChatServer.dir/ChatService.cc.o -c /home/mzy/Code/ChatServer/src/server/ChatService.cc

src/server/CMakeFiles/ChatServer.dir/ChatService.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/ChatService.cc.i"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/ChatServer/src/server/ChatService.cc > CMakeFiles/ChatServer.dir/ChatService.cc.i

src/server/CMakeFiles/ChatServer.dir/ChatService.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/ChatService.cc.s"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/ChatServer/src/server/ChatService.cc -o CMakeFiles/ChatServer.dir/ChatService.cc.s

src/server/CMakeFiles/ChatServer.dir/main.cpp.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/main.cpp.o: ../src/server/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/server/CMakeFiles/ChatServer.dir/main.cpp.o"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ChatServer.dir/main.cpp.o -c /home/mzy/Code/ChatServer/src/server/main.cpp

src/server/CMakeFiles/ChatServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/main.cpp.i"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/ChatServer/src/server/main.cpp > CMakeFiles/ChatServer.dir/main.cpp.i

src/server/CMakeFiles/ChatServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/main.cpp.s"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/ChatServer/src/server/main.cpp -o CMakeFiles/ChatServer.dir/main.cpp.s

src/server/CMakeFiles/ChatServer.dir/db/db.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/db/db.cc.o: ../src/server/db/db.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/server/CMakeFiles/ChatServer.dir/db/db.cc.o"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ChatServer.dir/db/db.cc.o -c /home/mzy/Code/ChatServer/src/server/db/db.cc

src/server/CMakeFiles/ChatServer.dir/db/db.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/db/db.cc.i"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/ChatServer/src/server/db/db.cc > CMakeFiles/ChatServer.dir/db/db.cc.i

src/server/CMakeFiles/ChatServer.dir/db/db.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/db/db.cc.s"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/ChatServer/src/server/db/db.cc -o CMakeFiles/ChatServer.dir/db/db.cc.s

src/server/CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.o: ../src/server/model/OfflineMsgModel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/server/CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.o"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.o -c /home/mzy/Code/ChatServer/src/server/model/OfflineMsgModel.cc

src/server/CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.i"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/ChatServer/src/server/model/OfflineMsgModel.cc > CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.i

src/server/CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.s"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/ChatServer/src/server/model/OfflineMsgModel.cc -o CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.s

src/server/CMakeFiles/ChatServer.dir/model/UserModel.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/model/UserModel.cc.o: ../src/server/model/UserModel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mzy/Code/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/server/CMakeFiles/ChatServer.dir/model/UserModel.cc.o"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ChatServer.dir/model/UserModel.cc.o -c /home/mzy/Code/ChatServer/src/server/model/UserModel.cc

src/server/CMakeFiles/ChatServer.dir/model/UserModel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/model/UserModel.cc.i"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mzy/Code/ChatServer/src/server/model/UserModel.cc > CMakeFiles/ChatServer.dir/model/UserModel.cc.i

src/server/CMakeFiles/ChatServer.dir/model/UserModel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/model/UserModel.cc.s"
	cd /home/mzy/Code/ChatServer/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mzy/Code/ChatServer/src/server/model/UserModel.cc -o CMakeFiles/ChatServer.dir/model/UserModel.cc.s

# Object files for target ChatServer
ChatServer_OBJECTS = \
"CMakeFiles/ChatServer.dir/ChatServer.cc.o" \
"CMakeFiles/ChatServer.dir/ChatService.cc.o" \
"CMakeFiles/ChatServer.dir/main.cpp.o" \
"CMakeFiles/ChatServer.dir/db/db.cc.o" \
"CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.o" \
"CMakeFiles/ChatServer.dir/model/UserModel.cc.o"

# External object files for target ChatServer
ChatServer_EXTERNAL_OBJECTS =

../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/ChatServer.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/ChatService.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/main.cpp.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/db/db.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/model/OfflineMsgModel.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/model/UserModel.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/build.make
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mzy/Code/ChatServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ../../../bin/ChatServer"
	cd /home/mzy/Code/ChatServer/build/src/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ChatServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/server/CMakeFiles/ChatServer.dir/build: ../bin/ChatServer

.PHONY : src/server/CMakeFiles/ChatServer.dir/build

src/server/CMakeFiles/ChatServer.dir/clean:
	cd /home/mzy/Code/ChatServer/build/src/server && $(CMAKE_COMMAND) -P CMakeFiles/ChatServer.dir/cmake_clean.cmake
.PHONY : src/server/CMakeFiles/ChatServer.dir/clean

src/server/CMakeFiles/ChatServer.dir/depend:
	cd /home/mzy/Code/ChatServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mzy/Code/ChatServer /home/mzy/Code/ChatServer/src/server /home/mzy/Code/ChatServer/build /home/mzy/Code/ChatServer/build/src/server /home/mzy/Code/ChatServer/build/src/server/CMakeFiles/ChatServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/server/CMakeFiles/ChatServer.dir/depend

