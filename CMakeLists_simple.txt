cmake_minimum_required(VERSION 3.16)
project(SimpleFileExplorer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable Qt MOC
set(CMAKE_AUTOMOC ON)

# Create executable
add_executable(SimpleFileExplorer src/main_simple.cpp)

# Link Qt6 libraries
target_link_libraries(SimpleFileExplorer Qt6::Core Qt6::Widgets)

# Compiler flags for optimization
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(SimpleFileExplorer PRIVATE -O3 -DNDEBUG)
endif()

# Set macOS app bundle properties
if(APPLE)
    set_target_properties(SimpleFileExplorer PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_STRING "Simple File Explorer for macOS"
        MACOSX_BUNDLE_BUNDLE_NAME "Simple File Explorer"
        MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0.0"
        MACOSX_BUNDLE_IDENTIFIER "com.example.SimpleFileExplorer"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.SimpleFileExplorer"
    )
endif() 