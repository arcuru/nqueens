#include "nqueens.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// Keeps loop from being optimized out
static uint64_t c;

// Returns the average runtime of the function over the given repetitions
double run_bench(uint64_t (*f)(size_t), size_t arg, uint32_t repetitions) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    for (size_t count = 0; count < repetitions; ++count) {
        c = f(arg);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<duration<double>>(end - start).count() / repetitions;
}

int main() {
    // List of all functions and their descriptor
    vector<tuple<string, size_t, uint64_t (*)(size_t)>> funcs = {
        make_tuple("  flat", 14, flat_queens),   // Flat
        make_tuple(" array", 14, array_queens),  // Array
        make_tuple("   dlx", 14, dlx_queens),    // Array
        make_tuple("   bit", 16, bit_queens),    // Bitwise
        make_tuple("thread", 17, thread_queens), // Threaded Bitwise
        make_tuple(" super", 17, super_queens),  // Super-awesome queens
    };

    // Options for which benchmarks to run
    vector<pair<uint32_t, uint32_t>> config = {
        {8, 1000}, // 8-queens * 1000 repetitions
        {9, 100},  //
        {10, 100}, //
        {11, 10},  //
        {12, 5},   //
        {13, 2},   //
        {14, 1},   //
        {15, 1},   //
        {16, 1},   //
        {17, 1},   //
    };
    cout.precision(6);
    cout << fixed;
    for (const auto y : config) {
        cout << " " << setw(2) << y.first << "-Queens\n";
        for (const auto x : funcs) {
            if (get<1>(x) < y.first) {
                continue;
            }
            auto avg_time = run_bench(get<2>(x), y.first, y.second);
            cout << get<0>(x) << '\t' << setw(8) << avg_time << " s\n";
        }
        cout << endl;
    }
}
