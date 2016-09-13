#include "nqueens.h"
#include <algorithm>
#include <vector>

namespace {

static uint64_t my_count = 0;

static void recurse(std::vector<size_t> &tmp, size_t idx) {
    if (tmp.size() == idx) {
        ++my_count;
        return;
    }
    // Loop through all possibilities for this place
    //  Using tmp.size() as a proxy for N
    for (size_t i = 0; i < tmp.size(); ++i) {
        // Lambda tests whether we have a conflict between 2 queens
        auto test = [&](size_t &x) {
            size_t diff = idx - (&x - &tmp.front());
            return ((i == x) || (i == x + diff) || (i == x - diff));
        };
        if (std::any_of(tmp.begin(), tmp.begin() + idx, test)) {
            continue;
        }
        tmp[idx] = i;
        recurse(tmp, idx + 1);
    }
}

} // Anonymous namespace

// Flat queens
// Solves Nqueens using a single vector of indices denoting queen placements
uint64_t flat_queens(size_t n) {
    my_count = 0;
    std::vector<size_t> x(n);
    recurse(x, 0);
    return my_count;
}
