// third-party dependencies
#include <as-ops.h>
#include <minimal-cmake/array.h>
#include <timer.h>

// system includes
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t elem_xy(as_point2i position, const int32_t width) {
  return position.x + position.y * width;
}

int32_t try_wrap(const int32_t index, const int32_t dim) {
  return ((index % dim) + dim) % dim;
}

as_point2i try_wrap_position(
  const as_point2i position, const int32_t width, const int32_t height) {
  return (as_point2i){
    .x = try_wrap(position.x, width), .y = try_wrap(position.y, height)};
}

int32_t alive_neighbors(
  const as_point2i position, const int32_t width, const int32_t height,
  const bool board[]) {
  const as_vec2i offsets[] = {{.x = -1, .y = 0}, {.x = -1, .y = -1},
                              {.x = 0, .y = -1}, {.x = 1, .y = -1},
                              {.x = 1, .y = 0},  {.x = 1, .y = 1},
                              {.x = 0, .y = 1},  {.x = -1, .y = 1}};
  int32_t living = 0;
  for (int32_t i = 0, count = sizeof(offsets) / sizeof(as_vec2i); i < count;
       i++) {
    living += board[elem_xy(
      try_wrap_position(
        as_point2i_add_vec2i(position, offsets[i]), width, height),
      width)];
  }
  return living;
}

// any live cell with fewer than two live neighbors dies, as if by
// underpopulation.
bool rule_1(
  as_point2i position, const int32_t width, const int32_t height,
  const bool board[]) {
  return board[elem_xy(position, width)]
      && alive_neighbors(position, width, height, board) < 2;
}

// any live cell with two or three live neighbors lives on to the next
// generation.
bool rule_2(
  const as_point2i position, const int32_t width, const int32_t height,
  const bool board[]) {
  const int32_t neighbors = alive_neighbors(position, width, height, board);
  return board[elem_xy(position, width)] && (neighbors == 2 || neighbors == 3);
}

// any live cell with more than three live neighbors dies, as if by
// overpopulation.
bool rule_3(
  const as_point2i position, const int32_t width, const int32_t height,
  const bool board[]) {
  return board[elem_xy(position, width)]
      && alive_neighbors(position, width, height, board) > 3;
}

// any dead cell with exactly three live neighbors becomes a live cell, as if by
// reproduction.
bool rule_4(
  const as_point2i position, const int32_t width, const int32_t height,
  const bool board[]) {
  return !board[elem_xy(position, width)]
      && alive_neighbors(position, width, height, board) == 3;
}

void update_board(const int32_t width, const int32_t height, bool board[]) {
  typedef struct change_t {
    int offset_;
    bool state_;
  } change_t;
  change_t* changes = NULL;
  for (int32_t y = 0; y < height; y++) {
    for (int32_t x = 0; x < width; x++) {
      const as_point2i position = (as_point2i){.x = x, .y = y};
      if (
        rule_1(position, width, height, board)
        || rule_3(position, width, height, board)) {
        array_push(
          changes,
          ((change_t){.offset_ = elem_xy(position, width), .state_ = false}));
      } else if (
        rule_2(position, width, height, board)
        || rule_4(position, width, height, board)) {
        array_push(
          changes,
          ((change_t){.offset_ = elem_xy(position, width), .state_ = true}));
      }
    }
  }
  for (int i = 0, size = array_size(changes); i < size; i++) {
    board[changes[i].offset_] = changes[i].state_;
  }
  array_free(changes);
}

void print_board(
  const int32_t width, const int32_t height, const bool board[]) {
  const char alive_dead_display[] = {'*', '@'};
  for (int32_t y = 0; y < height; y++) {
    for (int32_t x = 0; x < width; x++) {
      const as_point2i position = (as_point2i){.x = x, .y = y};
      printf("%c", alive_dead_display[board[elem_xy(position, width)]]);
    }
    printf("\n");
  }
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  timer_lib_initialize();

  enum { width = 40 };
  enum { height = 27 };

  bool board[height * width];
  memset(board, 0, height * width);

  // gosper glider gun
  board[elem_xy((as_point2i){2, 5}, width)] = true;
  board[elem_xy((as_point2i){2, 6}, width)] = true;
  board[elem_xy((as_point2i){3, 5}, width)] = true;
  board[elem_xy((as_point2i){3, 6}, width)] = true;

  board[elem_xy((as_point2i){12, 5}, width)] = true;
  board[elem_xy((as_point2i){12, 6}, width)] = true;
  board[elem_xy((as_point2i){12, 7}, width)] = true;
  board[elem_xy((as_point2i){13, 4}, width)] = true;
  board[elem_xy((as_point2i){13, 8}, width)] = true;
  board[elem_xy((as_point2i){14, 3}, width)] = true;
  board[elem_xy((as_point2i){14, 9}, width)] = true;
  board[elem_xy((as_point2i){15, 3}, width)] = true;
  board[elem_xy((as_point2i){15, 9}, width)] = true;
  board[elem_xy((as_point2i){16, 6}, width)] = true;
  board[elem_xy((as_point2i){17, 4}, width)] = true;
  board[elem_xy((as_point2i){17, 8}, width)] = true;
  board[elem_xy((as_point2i){18, 5}, width)] = true;
  board[elem_xy((as_point2i){18, 6}, width)] = true;
  board[elem_xy((as_point2i){18, 7}, width)] = true;
  board[elem_xy((as_point2i){19, 6}, width)] = true;

  board[elem_xy((as_point2i){22, 3}, width)] = true;
  board[elem_xy((as_point2i){22, 4}, width)] = true;
  board[elem_xy((as_point2i){22, 5}, width)] = true;
  board[elem_xy((as_point2i){23, 3}, width)] = true;
  board[elem_xy((as_point2i){23, 4}, width)] = true;
  board[elem_xy((as_point2i){23, 5}, width)] = true;
  board[elem_xy((as_point2i){24, 2}, width)] = true;
  board[elem_xy((as_point2i){24, 6}, width)] = true;
  board[elem_xy((as_point2i){26, 1}, width)] = true;
  board[elem_xy((as_point2i){26, 2}, width)] = true;
  board[elem_xy((as_point2i){26, 6}, width)] = true;
  board[elem_xy((as_point2i){26, 7}, width)] = true;

  board[elem_xy((as_point2i){36, 3}, width)] = true;
  board[elem_xy((as_point2i){36, 4}, width)] = true;
  board[elem_xy((as_point2i){37, 3}, width)] = true;
  board[elem_xy((as_point2i){37, 4}, width)] = true;

  // eater
  board[elem_xy((as_point2i){27, 20}, width)] = true;
  board[elem_xy((as_point2i){27, 21}, width)] = true;
  board[elem_xy((as_point2i){28, 20}, width)] = true;
  board[elem_xy((as_point2i){28, 21}, width)] = true;

  board[elem_xy((as_point2i){32, 21}, width)] = true;
  board[elem_xy((as_point2i){31, 22}, width)] = true;
  board[elem_xy((as_point2i){33, 22}, width)] = true;
  board[elem_xy((as_point2i){32, 23}, width)] = true;

  board[elem_xy((as_point2i){34, 23}, width)] = true;
  board[elem_xy((as_point2i){34, 24}, width)] = true;
  board[elem_xy((as_point2i){34, 25}, width)] = true;
  board[elem_xy((as_point2i){35, 25}, width)] = true;

  for (;;) {
    const double delay = 0.1; // wait for 1/10th of a second
    const tick_t time = timer_current();
    printf("\33[H\33[2J\33[3J");
    print_board(width, height, board);
    update_board(width, height, board);
    while (timer_elapsed(time) < delay) {
      // busy wait (ideally cross-platform sleep for some of this...)
    }
  }

  timer_lib_shutdown();

  return 0;
}
