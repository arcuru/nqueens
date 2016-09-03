#include "nqueens.h"
#include <future>
#include <vector>

using namespace std;

namespace {

// This struct hold the details per each level of iteration
struct board_row {
    uint32_t col;      // Bitmask for the columns
    uint32_t pos_diag; // Bitmask for the positive diagonal
    uint32_t neg_diag; // Bitmask for the negative diagonal
    uint32_t bits;     // Current bitmask
};

uint64_t helper(vector<board_row> stack, size_t ptr, uint32_t bitfield) {
    uint32_t lsb;
    uint64_t solutions = 0;
    uint32_t board_size = stack.size();
    const uint32_t mask = (1 << board_size) - 1;
    while (true) {
        if (0 == bitfield) {
            if (ptr == 0) {
                break;
            }
            bitfield = stack[ptr--].bits;
            continue;
        }
        // Pull out lowest on bit from bitfield
        lsb = -((signed)bitfield) & bitfield;
        bitfield ^= lsb; // Toggle off the bit

        if (ptr < (board_size - 1)) {
            const int n = ptr++;
            stack[ptr].col = stack[n].col | lsb;
            stack[ptr].neg_diag = (stack[n].neg_diag | lsb) >> 1;
            stack[ptr].pos_diag = (stack[n].pos_diag | lsb) << 1;
            stack[ptr].bits = bitfield;
            bitfield =
                mask &
                ~(stack[ptr].col | stack[ptr].neg_diag | stack[ptr].pos_diag);
            continue;
        } else {
            // We have no more rows to process; we found a solution.
            ++solutions;
            bitfield = stack[ptr--].bits;
            continue;
        }
    }
    return solutions;
}
} // anonymous namespace

//
// This is just a parallelized version of bit_queens
//
// Originally based on Jeff Somer's implementation:
//  See: http://www.jsomers.com/nqueen_demo/nqueens.html
//
uint64_t thread_queens(size_t board_size) {
    // Because of mirroring, this technique fails with a board size of < 2
    if (board_size == 0) {
        return 0;
    }
    if (board_size == 1) {
        return 1;
    }
    uint64_t solutions = 0;

    solutions = 0;
    vector<board_row> stack(board_size);

    size_t ptr = 1;
    uint32_t bitfield;
    const uint32_t mask = (1 << board_size) - 1;

    vector<future<uint64_t>> sub_routines;

    stack[0].col = stack[0].pos_diag = stack[0].neg_diag = stack[0].bits = 0;

    // Everything up to the center point
    for (uint32_t x = 1; x < (1 << (board_size >> 1)); x += x) {
        stack[1].col = x;
        stack[1].neg_diag = (x >> 1);
        stack[1].pos_diag = (x << 1);
        bitfield =
            mask & ~(stack[1].col | stack[1].neg_diag | stack[1].pos_diag);

        // Launch asynchronously
        sub_routines.push_back(
            async(launch::async, helper, stack, ptr, bitfield));
    }

    if (board_size & 1) {
        // Middle column
        bitfield = 1 << (board_size >> 1);
        stack[1].col = bitfield;
        stack[1].neg_diag = (bitfield >> 1);
        stack[1].pos_diag = (bitfield << 1);

        // This bitfield only covers half, since we'll flip the answers
        bitfield = (bitfield - 1) >> 1;

        // The middle column is half the size of the others
        // Run in this thread to avoid creating another one
        solutions += helper(stack, ptr, bitfield);
    }

    for (auto &x : sub_routines) {
        solutions += x.get();
    }

    // Double count since we only counted half
    solutions *= 2;
    return solutions;
}
