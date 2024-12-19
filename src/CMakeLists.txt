add_library(nqueens_core
    dlx_queens.cpp
    thread_queens.cpp
    flat_queens.cpp    # Added
    array_queens.cpp   # Added
    bit_queens.cpp     # Added
    super_queens.cpp   # Added
)

target_include_directories(nqueens_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(nqueens_core
    PUBLIC
        dlx
        Threads::Threads
)