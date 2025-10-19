# Project definition
cmake_minimum_required(VERSION 3.15)
project(Simple-DDS VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Enable testing for the whole project first.
enable_testing()

# 2. Fetch dependencies so they are available for all subdirectories.
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# This command makes gtest targets and the GoogleTest module available globally.
FetchContent_MakeAvailable(googletest)
  
  
# 3. Now that dependencies are ready, add the subdirectories that use them.
add_subdirectory(src)
add_subdirectory(tests)



