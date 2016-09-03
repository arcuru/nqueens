
set(NQUEENS_SOURCE_FILES
    array_queens.cpp
    flat_queens.cpp
    bit_queens.cpp
    thread_queens.cpp
)

add_library(nqueens_core ${NQUEENS_SOURCE_FILES})

