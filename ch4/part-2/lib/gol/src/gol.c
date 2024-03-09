#include "minimal-cmake-gol/gol.h"

#include <as-ops.h>
#include <minimal-cmake/array.h>

#include <stdlib.h>
#include <string.h>

struct mc_gol_board_t {
  int32_t width;
  int32_t height;
  bool* cells;
};

static int32_t elem_xy(as_point2i position, const int32_t width) {
  return position.x + position.y * width;
}

static int32_t try_wrap(const int32_t index, const int32_t dim) {
  return ((index % dim) + dim) % dim;
}

static as_point2i try_wrap_position(
  const as_point2i position, const int32_t width, const int32_t height) {
  return (as_point2i){
    .x = try_wrap(position.x, width), .y = try_wrap(position.y, height)};
}

static int32_t alive_neighbors(
  const as_point2i position, const mc_gol_board_t* board) {
  const as_vec2i offsets[] = {{.x = -1, .y = 0}, {.x = -1, .y = -1},
                              {.x = 0, .y = -1}, {.x = 1, .y = -1},
                              {.x = 1, .y = 0},  {.x = 1, .y = 1},
                              {.x = 0, .y = 1},  {.x = -1, .y = 1}};
  int32_t living = 0;
  for (int32_t i = 0, count = sizeof(offsets) / sizeof(as_vec2i); i < count;
       i++) {
    living += board->cells[elem_xy(
      try_wrap_position(
        as_point2i_add_vec2i(position, offsets[i]), board->width,
        board->height),
      board->width)];
  }
  return living;
}

// any live cell with fewer than two live neighbors dies, as if by
// underpopulation.
static bool rule_1(as_point2i position, const mc_gol_board_t* board) {
  return board->cells[elem_xy(position, board->width)]
      && alive_neighbors(position, board) < 2;
}

// any live cell with two or three live neighbors lives on to the next
// generation.
static bool rule_2(const as_point2i position, const mc_gol_board_t* board) {
  const int32_t neighbors = alive_neighbors(position, board);
  return board->cells[elem_xy(position, board->width)]
      && (neighbors == 2 || neighbors == 3);
}

// any live cell with more than three live neighbors dies, as if by
// overpopulation.
static bool rule_3(const as_point2i position, const mc_gol_board_t* board) {
  return board->cells[elem_xy(position, board->width)]
      && alive_neighbors(position, board) > 3;
}

// any dead cell with exactly three live neighbors becomes a live cell, as if by
// reproduction.
static bool rule_4(const as_point2i position, const mc_gol_board_t* board) {
  return !board->cells[elem_xy(position, board->width)]
      && alive_neighbors(position, board) == 3;
}

mc_gol_board_t* mc_gol_create_board(int32_t width, int32_t height) {
  mc_gol_board_t* board = malloc(sizeof(board));
  if (!board) {
    return NULL;
  }
  const int32_t size = width * height;
  bool* cells = malloc(size);
  if (!cells) {
    return NULL;
  }
  memset(cells, 0, size);
  board->width = width;
  board->height = height;
  board->cells = cells;
  return board;
}

void mc_gol_destroy_board(mc_gol_board_t* board) {
  free(board->cells);
  free(board);
}

int32_t mc_gol_board_width(const mc_gol_board_t* board) {
  return board->width;
}

int32_t mc_gol_board_height(const mc_gol_board_t* board) {
  return board->height;
}

bool mc_gol_board_cell(
  const mc_gol_board_t* board, const int32_t x, const int32_t y) {
  return board->cells[elem_xy((as_point2i){.x = x, .y = y}, board->width)];
}

void mc_gol_set_board_cell(
  mc_gol_board_t* board, const int32_t x, const int32_t y, const bool alive) {
  board->cells[elem_xy((as_point2i){.x = x, .y = y}, board->width)] = alive;
}

void mc_gol_update_board(mc_gol_board_t* board) {
  typedef struct change_t {
    int offset_;
    bool state_;
  } change_t;
  change_t* changes = NULL;
  for (int32_t y = 0; y < board->height; y++) {
    for (int32_t x = 0; x < board->width; x++) {
      const as_point2i position = (as_point2i){.x = x, .y = y};
      if (rule_1(position, board) || rule_3(position, board)) {
        mc_array_push(
          changes,
          ((change_t){
            .offset_ = elem_xy(position, board->width), .state_ = false}));
      } else if (rule_2(position, board) || rule_4(position, board)) {
        mc_array_push(
          changes,
          ((change_t){
            .offset_ = elem_xy(position, board->width), .state_ = true}));
      }
    }
  }
  for (int i = 0, size = mc_array_size(changes); i < size; i++) {
    board->cells[changes[i].offset_] = changes[i].state_;
  }
  mc_array_free(changes);
}
