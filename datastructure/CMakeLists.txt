project(datastructures)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Collect all header files in the current directory
file(GLOB_RECURSE HEADER_FILES "*.h")

# Collect all source files in the current directory
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

# Optionally, you can print the collected files for debugging
message(STATUS "Header files: ${HEADER_FILES}")
message(STATUS "Source files: ${SOURCE_FILES}")

add_library(datastructures ${HEADER_FILES} ${SOURCE_FILES})
