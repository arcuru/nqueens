
# Add unittests
add_executable(unittest unittests.cpp)
add_test(unittest unittest)
add_custom_command(TARGET unittest
                   POST_BUILD
                   COMMAND unittest
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Unittest needs to link with nqueens and the boost libs
target_link_libraries(unittest nqueens_core ${Boost_LIBRARIES})

add_executable(bench_queens benchmarks.cpp)
target_link_libraries(bench_queens nqueens_core)

