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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yg/phonebook

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yg/phonebook/build

# Utility rule file for phonebook_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/phonebook_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/phonebook_autogen.dir/progress.make

CMakeFiles/phonebook_autogen: phonebook_autogen/timestamp

phonebook_autogen/timestamp: /home/yg/Qt/6.9.1/gcc_64/libexec/moc
phonebook_autogen/timestamp: /home/yg/Qt/6.9.1/gcc_64/libexec/uic
phonebook_autogen/timestamp: CMakeFiles/phonebook_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/yg/phonebook/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target phonebook"
	/usr/bin/cmake -E cmake_autogen /home/yg/phonebook/build/CMakeFiles/phonebook_autogen.dir/AutogenInfo.json ""
	/usr/bin/cmake -E touch /home/yg/phonebook/build/phonebook_autogen/timestamp

phonebook_autogen: CMakeFiles/phonebook_autogen
phonebook_autogen: phonebook_autogen/timestamp
phonebook_autogen: CMakeFiles/phonebook_autogen.dir/build.make
.PHONY : phonebook_autogen

# Rule to build all files generated by this target.
CMakeFiles/phonebook_autogen.dir/build: phonebook_autogen
.PHONY : CMakeFiles/phonebook_autogen.dir/build

CMakeFiles/phonebook_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/phonebook_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/phonebook_autogen.dir/clean

CMakeFiles/phonebook_autogen.dir/depend:
	cd /home/yg/phonebook/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yg/phonebook /home/yg/phonebook /home/yg/phonebook/build /home/yg/phonebook/build /home/yg/phonebook/build/CMakeFiles/phonebook_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/phonebook_autogen.dir/depend

