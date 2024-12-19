cmake_policy(SET CMP0167 NEW)

# Locate Boost libraries: unit_test_framework
set(Boost_USE_STATIC_LIBS OFF)  # Changed from ON to OFF
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Add unittests
add_executable(unittest unittests.cpp)
add_test(unittest unittest)
add_custom_command(TARGET unittest
                   POST_BUILD
                   COMMAND unittest
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Unittest needs to link with nqueens and the boost libs
target_link_libraries(unittest 
    PRIVATE 
        nqueens_core 
        Boost::unit_test_framework
)

add_executable(bench_queens benchmarks.cpp)
target_link_libraries(bench_queens 
    PRIVATE 
        nqueens_core
)