# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = "F:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "F:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = G:\project\pushserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = G:\project\pushserver\build\mingw

# Include any dependencies generated for this target.
include src/CMakeFiles/pushserver.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/pushserver.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/pushserver.dir/flags.make

src/CMakeFiles/pushserver.dir/main.c.obj: src/CMakeFiles/pushserver.dir/flags.make
src/CMakeFiles/pushserver.dir/main.c.obj: src/CMakeFiles/pushserver.dir/includes_C.rsp
src/CMakeFiles/pushserver.dir/main.c.obj: ../../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\project\pushserver\build\mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/pushserver.dir/main.c.obj"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\pushserver.dir\main.c.obj   -c G:\project\pushserver\src\main.c

src/CMakeFiles/pushserver.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pushserver.dir/main.c.i"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E G:\project\pushserver\src\main.c > CMakeFiles\pushserver.dir\main.c.i

src/CMakeFiles/pushserver.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pushserver.dir/main.c.s"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S G:\project\pushserver\src\main.c -o CMakeFiles\pushserver.dir\main.c.s

src/CMakeFiles/pushserver.dir/main.c.obj.requires:

.PHONY : src/CMakeFiles/pushserver.dir/main.c.obj.requires

src/CMakeFiles/pushserver.dir/main.c.obj.provides: src/CMakeFiles/pushserver.dir/main.c.obj.requires
	$(MAKE) -f src\CMakeFiles\pushserver.dir\build.make src/CMakeFiles/pushserver.dir/main.c.obj.provides.build
.PHONY : src/CMakeFiles/pushserver.dir/main.c.obj.provides

src/CMakeFiles/pushserver.dir/main.c.obj.provides.build: src/CMakeFiles/pushserver.dir/main.c.obj


src/CMakeFiles/pushserver.dir/core/crc32.c.obj: src/CMakeFiles/pushserver.dir/flags.make
src/CMakeFiles/pushserver.dir/core/crc32.c.obj: src/CMakeFiles/pushserver.dir/includes_C.rsp
src/CMakeFiles/pushserver.dir/core/crc32.c.obj: ../../src/core/crc32.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\project\pushserver\build\mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/pushserver.dir/core/crc32.c.obj"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\pushserver.dir\core\crc32.c.obj   -c G:\project\pushserver\src\core\crc32.c

src/CMakeFiles/pushserver.dir/core/crc32.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pushserver.dir/core/crc32.c.i"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E G:\project\pushserver\src\core\crc32.c > CMakeFiles\pushserver.dir\core\crc32.c.i

src/CMakeFiles/pushserver.dir/core/crc32.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pushserver.dir/core/crc32.c.s"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S G:\project\pushserver\src\core\crc32.c -o CMakeFiles\pushserver.dir\core\crc32.c.s

src/CMakeFiles/pushserver.dir/core/crc32.c.obj.requires:

.PHONY : src/CMakeFiles/pushserver.dir/core/crc32.c.obj.requires

src/CMakeFiles/pushserver.dir/core/crc32.c.obj.provides: src/CMakeFiles/pushserver.dir/core/crc32.c.obj.requires
	$(MAKE) -f src\CMakeFiles\pushserver.dir\build.make src/CMakeFiles/pushserver.dir/core/crc32.c.obj.provides.build
.PHONY : src/CMakeFiles/pushserver.dir/core/crc32.c.obj.provides

src/CMakeFiles/pushserver.dir/core/crc32.c.obj.provides.build: src/CMakeFiles/pushserver.dir/core/crc32.c.obj


src/CMakeFiles/pushserver.dir/core/hash.c.obj: src/CMakeFiles/pushserver.dir/flags.make
src/CMakeFiles/pushserver.dir/core/hash.c.obj: src/CMakeFiles/pushserver.dir/includes_C.rsp
src/CMakeFiles/pushserver.dir/core/hash.c.obj: ../../src/core/hash.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\project\pushserver\build\mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/pushserver.dir/core/hash.c.obj"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\pushserver.dir\core\hash.c.obj   -c G:\project\pushserver\src\core\hash.c

src/CMakeFiles/pushserver.dir/core/hash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pushserver.dir/core/hash.c.i"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E G:\project\pushserver\src\core\hash.c > CMakeFiles\pushserver.dir\core\hash.c.i

src/CMakeFiles/pushserver.dir/core/hash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pushserver.dir/core/hash.c.s"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S G:\project\pushserver\src\core\hash.c -o CMakeFiles\pushserver.dir\core\hash.c.s

src/CMakeFiles/pushserver.dir/core/hash.c.obj.requires:

.PHONY : src/CMakeFiles/pushserver.dir/core/hash.c.obj.requires

src/CMakeFiles/pushserver.dir/core/hash.c.obj.provides: src/CMakeFiles/pushserver.dir/core/hash.c.obj.requires
	$(MAKE) -f src\CMakeFiles\pushserver.dir\build.make src/CMakeFiles/pushserver.dir/core/hash.c.obj.provides.build
.PHONY : src/CMakeFiles/pushserver.dir/core/hash.c.obj.provides

src/CMakeFiles/pushserver.dir/core/hash.c.obj.provides.build: src/CMakeFiles/pushserver.dir/core/hash.c.obj


src/CMakeFiles/pushserver.dir/core/hashmap.c.obj: src/CMakeFiles/pushserver.dir/flags.make
src/CMakeFiles/pushserver.dir/core/hashmap.c.obj: src/CMakeFiles/pushserver.dir/includes_C.rsp
src/CMakeFiles/pushserver.dir/core/hashmap.c.obj: ../../src/core/hashmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\project\pushserver\build\mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/pushserver.dir/core/hashmap.c.obj"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\pushserver.dir\core\hashmap.c.obj   -c G:\project\pushserver\src\core\hashmap.c

src/CMakeFiles/pushserver.dir/core/hashmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pushserver.dir/core/hashmap.c.i"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E G:\project\pushserver\src\core\hashmap.c > CMakeFiles\pushserver.dir\core\hashmap.c.i

src/CMakeFiles/pushserver.dir/core/hashmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pushserver.dir/core/hashmap.c.s"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S G:\project\pushserver\src\core\hashmap.c -o CMakeFiles\pushserver.dir\core\hashmap.c.s

src/CMakeFiles/pushserver.dir/core/hashmap.c.obj.requires:

.PHONY : src/CMakeFiles/pushserver.dir/core/hashmap.c.obj.requires

src/CMakeFiles/pushserver.dir/core/hashmap.c.obj.provides: src/CMakeFiles/pushserver.dir/core/hashmap.c.obj.requires
	$(MAKE) -f src\CMakeFiles\pushserver.dir\build.make src/CMakeFiles/pushserver.dir/core/hashmap.c.obj.provides.build
.PHONY : src/CMakeFiles/pushserver.dir/core/hashmap.c.obj.provides

src/CMakeFiles/pushserver.dir/core/hashmap.c.obj.provides.build: src/CMakeFiles/pushserver.dir/core/hashmap.c.obj


src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj: src/CMakeFiles/pushserver.dir/flags.make
src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj: src/CMakeFiles/pushserver.dir/includes_C.rsp
src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj: ../../src/core/mem_chain.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\project\pushserver\build\mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\pushserver.dir\core\mem_chain.c.obj   -c G:\project\pushserver\src\core\mem_chain.c

src/CMakeFiles/pushserver.dir/core/mem_chain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pushserver.dir/core/mem_chain.c.i"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E G:\project\pushserver\src\core\mem_chain.c > CMakeFiles\pushserver.dir\core\mem_chain.c.i

src/CMakeFiles/pushserver.dir/core/mem_chain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pushserver.dir/core/mem_chain.c.s"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S G:\project\pushserver\src\core\mem_chain.c -o CMakeFiles\pushserver.dir\core\mem_chain.c.s

src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj.requires:

.PHONY : src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj.requires

src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj.provides: src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj.requires
	$(MAKE) -f src\CMakeFiles\pushserver.dir\build.make src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj.provides.build
.PHONY : src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj.provides

src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj.provides.build: src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj


src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj: src/CMakeFiles/pushserver.dir/flags.make
src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj: src/CMakeFiles/pushserver.dir/includes_C.rsp
src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj: ../../src/core/mem_pool.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\project\pushserver\build\mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\pushserver.dir\core\mem_pool.c.obj   -c G:\project\pushserver\src\core\mem_pool.c

src/CMakeFiles/pushserver.dir/core/mem_pool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pushserver.dir/core/mem_pool.c.i"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E G:\project\pushserver\src\core\mem_pool.c > CMakeFiles\pushserver.dir\core\mem_pool.c.i

src/CMakeFiles/pushserver.dir/core/mem_pool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pushserver.dir/core/mem_pool.c.s"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S G:\project\pushserver\src\core\mem_pool.c -o CMakeFiles\pushserver.dir\core\mem_pool.c.s

src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj.requires:

.PHONY : src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj.requires

src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj.provides: src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj.requires
	$(MAKE) -f src\CMakeFiles\pushserver.dir\build.make src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj.provides.build
.PHONY : src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj.provides

src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj.provides.build: src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj


src/CMakeFiles/pushserver.dir/core/rbtree.c.obj: src/CMakeFiles/pushserver.dir/flags.make
src/CMakeFiles/pushserver.dir/core/rbtree.c.obj: src/CMakeFiles/pushserver.dir/includes_C.rsp
src/CMakeFiles/pushserver.dir/core/rbtree.c.obj: ../../src/core/rbtree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\project\pushserver\build\mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/CMakeFiles/pushserver.dir/core/rbtree.c.obj"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\pushserver.dir\core\rbtree.c.obj   -c G:\project\pushserver\src\core\rbtree.c

src/CMakeFiles/pushserver.dir/core/rbtree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pushserver.dir/core/rbtree.c.i"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E G:\project\pushserver\src\core\rbtree.c > CMakeFiles\pushserver.dir\core\rbtree.c.i

src/CMakeFiles/pushserver.dir/core/rbtree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pushserver.dir/core/rbtree.c.s"
	cd /d G:\project\pushserver\build\mingw\src && gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S G:\project\pushserver\src\core\rbtree.c -o CMakeFiles\pushserver.dir\core\rbtree.c.s

src/CMakeFiles/pushserver.dir/core/rbtree.c.obj.requires:

.PHONY : src/CMakeFiles/pushserver.dir/core/rbtree.c.obj.requires

src/CMakeFiles/pushserver.dir/core/rbtree.c.obj.provides: src/CMakeFiles/pushserver.dir/core/rbtree.c.obj.requires
	$(MAKE) -f src\CMakeFiles\pushserver.dir\build.make src/CMakeFiles/pushserver.dir/core/rbtree.c.obj.provides.build
.PHONY : src/CMakeFiles/pushserver.dir/core/rbtree.c.obj.provides

src/CMakeFiles/pushserver.dir/core/rbtree.c.obj.provides.build: src/CMakeFiles/pushserver.dir/core/rbtree.c.obj


# Object files for target pushserver
pushserver_OBJECTS = \
"CMakeFiles/pushserver.dir/main.c.obj" \
"CMakeFiles/pushserver.dir/core/crc32.c.obj" \
"CMakeFiles/pushserver.dir/core/hash.c.obj" \
"CMakeFiles/pushserver.dir/core/hashmap.c.obj" \
"CMakeFiles/pushserver.dir/core/mem_chain.c.obj" \
"CMakeFiles/pushserver.dir/core/mem_pool.c.obj" \
"CMakeFiles/pushserver.dir/core/rbtree.c.obj"

# External object files for target pushserver
pushserver_EXTERNAL_OBJECTS =

../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/main.c.obj
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/core/crc32.c.obj
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/core/hash.c.obj
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/core/hashmap.c.obj
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/core/rbtree.c.obj
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/build.make
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/linklibs.rsp
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/objects1.rsp
../../bin/pushserver.exe: src/CMakeFiles/pushserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=G:\project\pushserver\build\mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable ..\..\..\bin\pushserver.exe"
	cd /d G:\project\pushserver\build\mingw\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\pushserver.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/pushserver.dir/build: ../../bin/pushserver.exe

.PHONY : src/CMakeFiles/pushserver.dir/build

src/CMakeFiles/pushserver.dir/requires: src/CMakeFiles/pushserver.dir/main.c.obj.requires
src/CMakeFiles/pushserver.dir/requires: src/CMakeFiles/pushserver.dir/core/crc32.c.obj.requires
src/CMakeFiles/pushserver.dir/requires: src/CMakeFiles/pushserver.dir/core/hash.c.obj.requires
src/CMakeFiles/pushserver.dir/requires: src/CMakeFiles/pushserver.dir/core/hashmap.c.obj.requires
src/CMakeFiles/pushserver.dir/requires: src/CMakeFiles/pushserver.dir/core/mem_chain.c.obj.requires
src/CMakeFiles/pushserver.dir/requires: src/CMakeFiles/pushserver.dir/core/mem_pool.c.obj.requires
src/CMakeFiles/pushserver.dir/requires: src/CMakeFiles/pushserver.dir/core/rbtree.c.obj.requires

.PHONY : src/CMakeFiles/pushserver.dir/requires

src/CMakeFiles/pushserver.dir/clean:
	cd /d G:\project\pushserver\build\mingw\src && $(CMAKE_COMMAND) -P CMakeFiles\pushserver.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/pushserver.dir/clean

src/CMakeFiles/pushserver.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" G:\project\pushserver G:\project\pushserver\src G:\project\pushserver\build\mingw G:\project\pushserver\build\mingw\src G:\project\pushserver\build\mingw\src\CMakeFiles\pushserver.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/pushserver.dir/depend

