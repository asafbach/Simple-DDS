# Project definition
cmake_minimum_required(VERSION 3.15)
project(Simple-DDS VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Subdirectories ---
# Add the source and test directories to the build
add_subdirectory(src)
add_subdirectory(tests)

# --- Dependencies ---
# Fetch Google Test for our unit testing framework
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()
