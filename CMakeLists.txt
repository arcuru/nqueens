cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0048 NEW)  # for project version handling
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)  # for modern Boost finding
endif()


project(nqueens 
    VERSION 1.0
    LANGUAGES CXX)

# Modern CMake: Set C++ standard globally
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output compilation database for clangtidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Modern threading support
find_package(Threads REQUIRED)

# Configure Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Include DLX
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/dlx)
target_include_directories(dlx 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/deps/dlx
)

# Build nqueens lib
add_subdirectory(src)

# Enable testing
include(CTest)
add_subdirectory(test)