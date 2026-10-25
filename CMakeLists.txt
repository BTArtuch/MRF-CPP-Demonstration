cmake_minimum_required(VERSION 3.10)
project(MRF_CPP_Demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output binaries to the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Include headers directory
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Build Target 1: Phantom Generator
add_executable(phantom_generator src/phantom_generator.cpp)
target_link_libraries(phantom_generator ${OpenCV_LIBS})