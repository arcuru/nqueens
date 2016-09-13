#include "nqueens.h"
#include "dlx.h"

uint64_t dlx_queens(size_t n) {
    // Construct vector of vectors for nqueens problem
    std::vector<std::vector<size_t>> definition;
    definition.reserve(n * n);

    // One entry per square
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            definition.emplace_back();
            auto &tmp = definition.back();
            tmp.reserve(4);

            // Row is simply row value
            tmp.push_back(r);

            // Column is N + column
            tmp.push_back(n + c);

            // Diags are more complicated (and optional)
            tmp.push_back(n + n + (n - 1) + r - c);
            tmp.push_back(n + n + n + (n - 1) + c + r);
        }
    }

    // Create DLX and return the count
    DLX tmp(definition, 2 * n);
    return tmp.count_solutions();
}
