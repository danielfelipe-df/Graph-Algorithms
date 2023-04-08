cmake_minimum_required(VERSION 3.10)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name
project(Algorithms
  VERSION 1.0
  DESCRIPTION "Algorithms in Graph Theory"
  LANGUAGES CXX C
  )


# Add the flags for the sanitizer and errors
set(CMAKE_CXX_FLAGS "-Wall -Werror -g -fsanitize=address -fsanitize=leak")

# Set the name of the target
set(TARGET_NAME graphAlgorithms)

# Add the executable
add_executable(${TARGET_NAME} main.cpp)

# Add the dir of the headers
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Add the sources
target_sources(${TARGET_NAME} PRIVATE
  src/graph.cpp
  )
