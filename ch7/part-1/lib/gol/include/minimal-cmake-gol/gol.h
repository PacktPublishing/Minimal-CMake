#ifndef MC_GOL_H
#define MC_GOL_H

#include "mc_gol_export.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct mc_gol_board_t mc_gol_board_t;

// lifetime
MC_GOL_EXPORT mc_gol_board_t* mc_gol_create_board(
  int32_t width, int32_t height);
MC_GOL_EXPORT void mc_gol_destroy_board(mc_gol_board_t* board);

// process
MC_GOL_EXPORT void mc_gol_update_board(mc_gol_board_t* board);

// queries
MC_GOL_EXPORT int32_t mc_gol_board_width(const mc_gol_board_t* board);
MC_GOL_EXPORT int32_t mc_gol_board_height(const mc_gol_board_t* board);
MC_GOL_EXPORT bool mc_gol_board_cell(
  const mc_gol_board_t* board, int32_t x, int32_t y);

// mutations
MC_GOL_EXPORT void mc_gol_set_board_cell(
  mc_gol_board_t* board, int32_t x, int32_t y, bool alive);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MC_GOL_H
