#pragma once
#include <cstdint>

using std::size_t;

uint64_t flat_queens(size_t n);

uint64_t array_queens(size_t n);

uint64_t dlx_queens(size_t n);

uint64_t bit_queens(size_t n);

uint64_t thread_queens(size_t n);

uint64_t super_queens(size_t n);
