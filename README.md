[![Build Status](https://travis-ci.org/patricksjackson/nqueens.svg?branch=master)](https://travis-ci.org/patricksjackson/nqueens)

# N-Queens 6 ways
The [8-Queens puzzle](https://en.wikipedia.org/wiki/Eight_queens_puzzle) is a staple of intro programming courses. The problem boils down to one simple question: How many possible ways can you arrange 8 Queens on a chessboard with none able to attack any other?

To the experienced programmer this is not exactly difficult, but to a beginner it's a good exercise. You have to decide how to represent the data, whether to use recursion or basic loops, and whether you can brute force it or need to optimize it.

It's a good teaching tool.

This repo takes it one step further with the general version: each code snippet here solves the N-Queens puzzle. i.e. How many ways can we place N Queens on and NxN chessboard?

# Building

When cloning the repo, you need to pass the `--recursive` option to git. This project includes [dlx-cpp](https://github.com/patricksjackson/dlx-cpp) as a submodule for one of the solutions.

```
git clone --recursive https://github.com/patricksjackson/nqueens.git
cd nqueens
mkdir build
cd build
cmake ..
make
```

`Make` will run the unittests every time it's built. The mini benchmarking suite executable will be placed at `/build/test/bench_queens`.

# Solutions

The 6 solutions contained within have wildly different performance profiles and solving techniques.

## 1. 'Flat' Queens
This is the least efficient solution, yet it is certainly the cleanest to read. It's `Flat` because all it does is recursively iterate/backtrack over a 1D vector of row indices for the queens. It's also only ~15 lines of code.

## 2. 'Array' Queens
This solution is an ugly one. It's what I wrote years ago when I first encountered the problem back in college. It sets up a 2D array representing the chessboard the use to place Queens.

## 3. DLX Queens
This is the cop-out way of solving the problem. It uses a library, [dlx-cpp](https://github.com/patricksjackson/dlx-cpp) implementing Knuth's Dancing Links algorithm.

## 4. 'Bitwise' Queens
This uses a backtracking algorithm utilizing individual bits to keep track of the placement of the queens. The version included here is a heavily modified version of an algorithm written by Jeff Somers. More information about it can be found [here](http://www.jsomers.com/nqueen_demo/nqueens.html).

## 5. 'Thread' Queens
This uses the same core solver as 'Bitwise' Queens, but multithreads the algorithm. It create N/2 separate tasks to run the calculations, and scales linearly to extra cores (minus the thread creation overhead).

## 6. 'Super Awesome' Queens
This is the greatest solution to the problem I've ever seen. You'll just have to check out [the code](https://github.com/patricksjackson/nqueens/blob/master/src/super_queens.cpp).
