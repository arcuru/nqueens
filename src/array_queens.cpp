#include <stdlib.h>

#include <vector>

#include "nqueens.h"

namespace {

int nRows;
int nCols;

int currentCol = 0;
std::vector<std::vector<int>> Board;
std::vector<int> queenRow;

// Tests if the given move is a legal move
bool isLegal(int row, int col) { return Board[row][col] == 0; }

// Queen - Places/Removes Queen
// Marks each place on the board like spokes from the queen
// Looks long but is more efficient doing each continuos line
void Queen(int row, int col, bool in) {
  int plus = in ? 1 : -1;
  int r, c;
  // Up Right
  r = row - 1;
  c = col + 1;
  while ((r >= 0) && (c < nCols)) {
    Board[r][c] += plus;
    r--;
    c++;
  }
  // Down Right
  r = row + 1;
  c = col + 1;
  while ((r < nRows) && (c < nCols)) {
    Board[r][c] += plus;
    r++;
    c++;
  }
  // Right
  c = col + 1;
  while (c < nCols) {
    Board[row][c] += plus;
    c++;
  }

  Board[row][col] = in ? -1 : 0;
}

// Places Queen in the current column
void Place(int row) {
  queenRow[currentCol] = row;
  Queen(row, currentCol, true);
  currentCol++;
}

// Removes Queen from the current column
void Remove() {
  int row = queenRow[currentCol];
  int col = currentCol;
  Queen(row, col, false);
  queenRow[currentCol] = -1;
}

// Process Column
// Find the next legal location in the specified column, place a queen there,
// and advance
bool ProcessColumn() {
  int row = queenRow[currentCol] + 1;
  if (queenRow[currentCol] >= 0) {
    Remove();
  }
  while (row < nRows) {
    if (isLegal(row, currentCol)) {
      Place(row);
      return true;
    }
    row++;
  }
  return false;
}
}  // anonymous namespace

// Array-based queens
// Solves the N-queens problem using a 2D array, placing queens in each column
uint64_t array_queens(size_t n) {
  nRows = n;
  nCols = nRows;
  Board.resize(nRows);
  for (auto &v : Board) {
    v.resize(nRows);
  }
  queenRow.resize(nRows);

  int i;
  int solution = 0;
  for (i = 0; i < nCols; i++) {
    queenRow[i] = -1;
  }
  while (currentCol >= 0) {
    bool cow = ProcessColumn();
    if (!cow) {
      --currentCol;
    }
    if (currentCol == nCols) {
      ++solution;
      --currentCol;
    }
  }
  currentCol = 0;
  Board.clear();
  queenRow.clear();
  return solution;
}
