cmake_minimum_required(VERSION 2.8)

# Output compilation database for clangtidy
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set default build type to Release
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Enable C++14 features on gcc/clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

# Enable Warnings
# Clang has different warnings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics -pedantic -Wall -Wextra -Wshadow -Werror")
    set(CMAKE_CXX_FLAGS_DEBUG "-Og")
    set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Add library includes
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Include DLX
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/dlx EXCLUDE_FROM_ALL)
include_directories(${CMAKE_SOURCE_DIR}/deps/dlx)

# Build nqueens lib and add to include path
add_subdirectory(src)
include_directories(src)

# Add tests
enable_testing()
add_subdirectory(test)

