# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/etsuko/Application/explorer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/etsuko/Application/explorer/build

# Include any dependencies generated for this target.
include CMakeFiles/MacFileExplorer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MacFileExplorer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MacFileExplorer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MacFileExplorer.dir/flags.make

MacFileExplorer_autogen/timestamp: /opt/homebrew/opt/qt@6/share/qt/libexec/moc
MacFileExplorer_autogen/timestamp: /opt/homebrew/opt/qt@6/share/qt/libexec/uic
MacFileExplorer_autogen/timestamp: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target MacFileExplorer"
	/opt/homebrew/bin/cmake -E cmake_autogen /Users/etsuko/Application/explorer/build/CMakeFiles/MacFileExplorer_autogen.dir/AutogenInfo.json Release
	/opt/homebrew/bin/cmake -E touch /Users/etsuko/Application/explorer/build/MacFileExplorer_autogen/timestamp

CMakeFiles/MacFileExplorer.dir/codegen:
.PHONY : CMakeFiles/MacFileExplorer.dir/codegen

CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.o: MacFileExplorer_autogen/mocs_compilation.cpp
CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.o -MF CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.o -c /Users/etsuko/Application/explorer/build/MacFileExplorer_autogen/mocs_compilation.cpp

CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/build/MacFileExplorer_autogen/mocs_compilation.cpp > CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.i

CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/build/MacFileExplorer_autogen/mocs_compilation.cpp -o CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.s

CMakeFiles/MacFileExplorer.dir/src/main.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/src/main.cpp.o: /Users/etsuko/Application/explorer/src/main.cpp
CMakeFiles/MacFileExplorer.dir/src/main.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MacFileExplorer.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/src/main.cpp.o -MF CMakeFiles/MacFileExplorer.dir/src/main.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/src/main.cpp.o -c /Users/etsuko/Application/explorer/src/main.cpp

CMakeFiles/MacFileExplorer.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/src/main.cpp > CMakeFiles/MacFileExplorer.dir/src/main.cpp.i

CMakeFiles/MacFileExplorer.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/src/main.cpp -o CMakeFiles/MacFileExplorer.dir/src/main.cpp.s

CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.o: /Users/etsuko/Application/explorer/src/MainWindow.cpp
CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.o -MF CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.o -c /Users/etsuko/Application/explorer/src/MainWindow.cpp

CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/src/MainWindow.cpp > CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.i

CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/src/MainWindow.cpp -o CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.s

CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.o: /Users/etsuko/Application/explorer/src/FileSystemModel.cpp
CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.o -MF CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.o -c /Users/etsuko/Application/explorer/src/FileSystemModel.cpp

CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/src/FileSystemModel.cpp > CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.i

CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/src/FileSystemModel.cpp -o CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.s

CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.o: /Users/etsuko/Application/explorer/src/SearchEngine.cpp
CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.o -MF CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.o -c /Users/etsuko/Application/explorer/src/SearchEngine.cpp

CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/src/SearchEngine.cpp > CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.i

CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/src/SearchEngine.cpp -o CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.s

CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.o: /Users/etsuko/Application/explorer/src/FileIndexer.cpp
CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.o -MF CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.o -c /Users/etsuko/Application/explorer/src/FileIndexer.cpp

CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/src/FileIndexer.cpp > CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.i

CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/src/FileIndexer.cpp -o CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.s

CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.o: /Users/etsuko/Application/explorer/src/AdvancedSearch.cpp
CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.o -MF CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.o -c /Users/etsuko/Application/explorer/src/AdvancedSearch.cpp

CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/src/AdvancedSearch.cpp > CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.i

CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/src/AdvancedSearch.cpp -o CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.s

CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.o: /Users/etsuko/Application/explorer/src/MacOSIntegration.cpp
CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.o -MF CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.o -c /Users/etsuko/Application/explorer/src/MacOSIntegration.cpp

CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/src/MacOSIntegration.cpp > CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.i

CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/src/MacOSIntegration.cpp -o CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.s

CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.o: /Users/etsuko/Application/explorer/src/PreviewWidget.cpp
CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.o -MF CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.o -c /Users/etsuko/Application/explorer/src/PreviewWidget.cpp

CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/src/PreviewWidget.cpp > CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.i

CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/src/PreviewWidget.cpp -o CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.s

CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.o: CMakeFiles/MacFileExplorer.dir/flags.make
CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.o: /Users/etsuko/Application/explorer/src/StatusBarWidget.cpp
CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.o: CMakeFiles/MacFileExplorer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.o -MF CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.o.d -o CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.o -c /Users/etsuko/Application/explorer/src/StatusBarWidget.cpp

CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/etsuko/Application/explorer/src/StatusBarWidget.cpp > CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.i

CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/etsuko/Application/explorer/src/StatusBarWidget.cpp -o CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.s

# Object files for target MacFileExplorer
MacFileExplorer_OBJECTS = \
"CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/MacFileExplorer.dir/src/main.cpp.o" \
"CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.o" \
"CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.o" \
"CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.o" \
"CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.o" \
"CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.o" \
"CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.o" \
"CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.o" \
"CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.o"

# External object files for target MacFileExplorer
MacFileExplorer_EXTERNAL_OBJECTS =

MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/MacFileExplorer_autogen/mocs_compilation.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/src/main.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/src/MainWindow.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/src/FileSystemModel.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/src/SearchEngine.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/src/FileIndexer.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/src/AdvancedSearch.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/src/MacOSIntegration.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/src/PreviewWidget.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/src/StatusBarWidget.cpp.o
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/build.make
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: /opt/homebrew/opt/qt@6/lib/QtWidgets.framework/Versions/A/QtWidgets
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: /opt/homebrew/opt/qt@6/lib/QtGui.framework/Versions/A/QtGui
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: /opt/homebrew/opt/qt@6/lib/QtConcurrent.framework/Versions/A/QtConcurrent
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: /opt/homebrew/opt/qt@6/lib/QtCore.framework/Versions/A/QtCore
MacFileExplorer.app/Contents/MacOS/MacFileExplorer: CMakeFiles/MacFileExplorer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/etsuko/Application/explorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable MacFileExplorer.app/Contents/MacOS/MacFileExplorer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MacFileExplorer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MacFileExplorer.dir/build: MacFileExplorer.app/Contents/MacOS/MacFileExplorer
.PHONY : CMakeFiles/MacFileExplorer.dir/build

CMakeFiles/MacFileExplorer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MacFileExplorer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MacFileExplorer.dir/clean

CMakeFiles/MacFileExplorer.dir/depend: MacFileExplorer_autogen/timestamp
	cd /Users/etsuko/Application/explorer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/etsuko/Application/explorer /Users/etsuko/Application/explorer /Users/etsuko/Application/explorer/build /Users/etsuko/Application/explorer/build /Users/etsuko/Application/explorer/build/CMakeFiles/MacFileExplorer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MacFileExplorer.dir/depend

