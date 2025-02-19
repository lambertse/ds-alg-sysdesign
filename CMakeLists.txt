cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDDARD 17)
set(CMAKE_CXX_STANDDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# Make Google Test available
FetchContent_MakeAvailable(googletest)
include_directories(${googletest_SOURCE_DIR}/googletest/include/)
include_directories(datastructure/)

add_subdirectory(datastructure/balanced_binary_tree)
add_subdirectory(datastructure/skip_list)
