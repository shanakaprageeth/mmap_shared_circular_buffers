# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(mmap_shm LANGUAGES CXX C VERSION 0.0.1)

# CPP Standard to be used
set(CMAKE_CXX_STANDARD 14)

# COMPILER DEBUG FLAGS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")

# CMAKE Library build
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# BUILD OUTPUT DIRECTORIES
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

# INCLUDE Directory
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYFILE_SOURCE_DIR
      "${CMAKE_SOURCE_DIR}/include/sample/ ${CMAKE_SOURCE_DIR}/tests/"
  )
  set(DOXYFILE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/sample/)

  set(DOXYGEN_NAME gtest_test)
  set(DOXYFILE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  set(DOXYFILE_PROJECT_NAME "GTest Tests")
  set(DOXYFILE_PROJECT_VERSION
      "${PROJECT_VERSION}"
  )
  set(DOXYFILE_LATEX "OFF")

  include(UseDoxygen OPTIONAL)
endif(DOXYGEN_FOUND)

include_directories($INCLUDE_DIR)

# Sub directories to compile
add_subdirectory(src)
add_subdirectory(apps)
