#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t elem_rc(const size_t row, const size_t col, const size_t cols) {
  return row * cols + col;
}

size_t try_wrap(const int64_t index, const int64_t dim) {
  return ((index % dim) + dim) % dim;
}

size_t alive_neighbors(
  const size_t row, const size_t col, const size_t rows, const size_t cols,
  const bool board[]) {
  typedef struct adjust_t {
    int64_t r;
    int64_t c;
  } adjust_t;
  const adjust_t adjusts[] = {{.r = 0, .c = -1}, {.r = -1, .c = -1},
                              {.r = -1, .c = 0}, {.r = -1, .c = 1},
                              {.r = 0, .c = 1},  {.r = 1, .c = 1},
                              {.r = 1, .c = 0},  {.r = 1, .c = -1}};
  size_t living = 0;
  for (size_t i = 0, count = sizeof(adjusts) / sizeof(adjust_t); i < count;
       i++) {
    living += board[elem_rc(
      try_wrap((int64_t)row + adjusts[i].r, (int64_t)rows),
      try_wrap((int64_t)col + adjusts[i].c, (int64_t)cols), cols)];
  }
  return living;
}

// any live cell with fewer than two live neighbors dies, as if by
// underpopulation.
bool rule_1(
  const size_t row, const size_t col, const size_t rows, const size_t cols,
  const bool board[]) {
  return board[elem_rc(row, col, cols)]
      && alive_neighbors(row, col, rows, cols, board) < 2;
}

// any live cell with two or three live neighbors lives on to the next
// generation.
bool rule_2(
  const size_t row, const size_t col, const size_t rows, const size_t cols,
  const bool board[]) {
  const size_t neighbors = alive_neighbors(row, col, rows, cols, board);
  return board[elem_rc(row, col, cols)] && (neighbors == 2 || neighbors == 3);
}

// any live cell with more than three live neighbors dies, as if by
// overpopulation.
bool rule_3(
  const size_t row, const size_t col, const size_t rows, const size_t cols,
  const bool board[]) {
  return board[elem_rc(row, col, cols)]
      && alive_neighbors(row, col, rows, cols, board) > 3;
}

// any dead cell with exactly three live neighbors becomes a live cell, as if by
// reproduction.
bool rule_4(
  const size_t row, const size_t col, const size_t rows, const size_t cols,
  const bool board[]) {
  return !board[elem_rc(row, col, cols)]
      && alive_neighbors(row, col, rows, cols, board) == 3;
}

void update_board(const size_t rows, const size_t cols, bool in_out_board[]) {
  bool* original_board = malloc(rows * cols);
  memcpy(original_board, in_out_board, sizeof(bool) * rows * cols);
  for (size_t row = 0; row < rows; row++) {
    for (size_t col = 0; col < cols; col++) {
      if (
        rule_1(row, col, rows, cols, original_board)
        || rule_3(row, col, rows, cols, original_board)) {
        in_out_board[elem_rc(row, col, cols)] = false;
      } else if (
        rule_2(row, col, rows, cols, original_board)
        || rule_4(row, col, rows, cols, original_board)) {
        in_out_board[elem_rc(row, col, cols)] = true;
      }
    }
  }
  free(original_board);
}

void print_board(const size_t rows, const size_t cols, const bool board[]) {
  const char alive_dead_display[] = {'*', '@'};
  for (size_t row = 0; row < rows; row++) {
    for (size_t col = 0; col < cols; col++) {
      printf("%c", alive_dead_display[board[elem_rc(row, col, cols)]]);
    }
    printf("\n");
  }
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  enum { cols = 40 };
  enum { rows = 20 };

  bool board[rows * cols];
  memset(board, 0, rows * cols);

  // glider
  board[elem_rc(10, 7, cols)] = true;
  board[elem_rc(11, 8, cols)] = true;
  board[elem_rc(11, 9, cols)] = true;
  board[elem_rc(10, 9, cols)] = true;
  board[elem_rc(9, 9, cols)] = true;

  for (;;) {
    printf("\33[H\33[2J\33[3J");
    print_board(rows, cols, board);
    update_board(rows, cols, board);
    getchar();
  }

  return 0;
}
