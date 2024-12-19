#include <chrono>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

#include "nqueens.h"

using namespace std;

// Returns the average runtime of the function over the given repetitions
template <class F, class... Args>
auto test(F f, size_t repetitions, Args &&...args) {
  using namespace std::chrono;
  auto start = high_resolution_clock::now();
  auto res = f(std::forward<Args>(args)...);
  for (size_t count = 1; count < repetitions; ++count) {
    res = f(std::forward<Args>(args)...);
  }
  auto end = high_resolution_clock::now();
  auto time =
      duration_cast<duration<double>>(end - start).count() / repetitions;
  return make_pair(res, time);
}

int main() {
  // List of all functions and their descriptor
  vector<tuple<string, size_t, uint64_t (*)(size_t)>> funcs = {
      make_tuple("  flat", 14, flat_queens),    // Flat
      make_tuple(" array", 14, array_queens),   // Array
      make_tuple("   dlx", 14, dlx_queens),     // Array
      make_tuple("   bit", 16, bit_queens),     // Bitwise
      make_tuple("thread", 17, thread_queens),  // Threaded Bitwise
      make_tuple(" super", 17, super_queens),   // Super-awesome queens
  };

  // Options for which benchmarks to run
  vector<pair<uint32_t, uint32_t>> config = {
      {8, 1000},  // 8-queens * 1000 repetitions
      {9, 100},   //
      {10, 100},  //
      {11, 10},   //
      {12, 5},    //
      {13, 2},    //
      {14, 1},    //
      {15, 1},    //
      {16, 1},    //
      {17, 1},    //
  };
  cout.precision(6);
  cout << fixed;
  for (const auto &y : config) {
    cout << " " << setw(2) << y.first << "-Queens\n";
    for (const auto &x : funcs) {
      if (get<1>(x) < y.first) {
        continue;
      }
      auto avg_time = test(get<2>(x), y.second, y.first);
      cout << get<0>(x) << '\t' << setw(8) << get<1>(avg_time) << " s\n";
    }
    cout << endl;
  }
}
