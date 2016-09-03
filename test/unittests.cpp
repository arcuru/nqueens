#include "nqueens.h"
#include <map>
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

const std::vector<uint64_t> expected = {
    0,
    1,            // 1
    0,            // 2
    0,            // 3
    2,            // 4
    10,           // 5
    4,            // 6
    40,           // 7
    92,           // 8
    352,          // 9
    724,          // 10
    2680,         // 11
    14200,        // 12
    73712,        // 13
    365596,       // 14
    2279184,      // 15
    14772512,     // 16
    95815104,     // 17
    666090624,    // 18
    4968057848,   // 19
    39029188884,  // 20
    314666222712, // 21
};

BOOST_AUTO_TEST_CASE(test_array_queens) {
    for (unsigned int i = 1; i < 13; ++i)
        BOOST_REQUIRE_EQUAL(array_queens(i), expected.at(i));
}

BOOST_AUTO_TEST_CASE(test_flat_queens) {
    for (unsigned int i = 1; i < 13; ++i)
        BOOST_REQUIRE_EQUAL(flat_queens(i), expected.at(i));
}

BOOST_AUTO_TEST_CASE(test_bit_queens) {
    for (unsigned int i = 1; i < 13; ++i)
        BOOST_REQUIRE_EQUAL(bit_queens(i), expected.at(i));
}

BOOST_AUTO_TEST_CASE(test_thread_queens) {
    for (unsigned int i = 1; i < 13; ++i)
        BOOST_REQUIRE_EQUAL(thread_queens(i), expected.at(i));
}
