#include "nqueens.h"
#include <vector>

//
// Bitwise queens solution
//
// This algorithm was originally based on a solution by Jeff Somers
//  See: http://www.jsomers.com/nqueen_demo/nqueens.html
//
uint64_t bit_queens(size_t n) {
    // Because of mirroring, this technique fails with a board size of < 2
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    uint64_t solutions = 0;

    // This struct hold the details per each level of iteration
    struct board_row {
        uint32_t col;      // Bitmask for the columns
        uint32_t pos_diag; // Bitmask for the positive diagonal
        uint32_t neg_diag; // Bitmask for the negative diagonal
        uint32_t bits;     // Current bitmask
    };

    std::vector<board_row> stack(n);

    uint32_t ptr = 0;
    uint32_t lsb;
    uint32_t bitfield;
    const size_t odd = n & 1;
    const uint32_t mask = (1 << n) - 1;

    for (size_t i = 0; i < (1 + odd); ++i) {
        if (0 == i) {
            /* Handle half of the board, except the middle
               column. So if the board is 5 x 5, the first
               row will be: 00011, since we're not worrying
               about placing a queen in the center column (yet).
            */
            const uint32_t half = n >> 1; /* divide by two */
            bitfield = (1 << half) - 1;
            stack[0].col = stack[0].pos_diag = stack[0].neg_diag = 0;
        } else {
            /* Handle the middle column (of a odd-sized board).
               Set middle column bit to 1, then set
               half of next row.
               So we're processing first row (one element) & half of next.
               So if the board is 5 x 5, the first row will be: 00100, and
               the next row will be 00011.
            */
            bitfield = 1 << (n >> 1);
            ptr = 1;

            // The first row just has one queen (in the middle column).
            stack[0].col = stack[0].pos_diag = stack[0].neg_diag = 0;
            stack[0].bits = 0;

            // Now do the next row.  Only set bits in half of it, because we'll
            // flip the results over the "Y-axis".
            stack[1].col = bitfield;
            stack[1].neg_diag = (bitfield >> 1);
            stack[1].pos_diag = (bitfield << 1);

            /* bitfield -1 is all 1's to the left of the single 1 */
            bitfield = (bitfield - 1) >> 1;
        }

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

            if (ptr < (n - 1)) {
                const size_t ind = ptr++;
                stack[ptr].col = stack[ind].col | lsb;
                stack[ptr].neg_diag = (stack[ind].neg_diag | lsb) >> 1;
                stack[ptr].pos_diag = (stack[ind].pos_diag | lsb) << 1;
                stack[ptr].bits = bitfield;
                bitfield = mask &
                           ~(stack[ptr].col | stack[ptr].neg_diag |
                             stack[ptr].pos_diag);
                continue;
            } else {
                // We have no more rows to process; we found a solution.
                ++solutions;
                bitfield = stack[ptr--].bits;
                continue;
            }
        }
    }

    // Double count since we only counted half
    solutions *= 2;
    return solutions;
}
