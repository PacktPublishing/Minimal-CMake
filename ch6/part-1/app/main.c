// third-party dependencies
#include <as-ops.h>
#include <minimal-cmake-gol/gol.h>
#include <timer.h>

// system includes
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_syswm.h>

// void print_board(const mc_gol_board_t* board) {
//   const char alive_dead_display[] = {'*', '@'};
//   for (int32_t y = 0, height = mc_gol_board_height(board); y < height; y++) {
//     for (int32_t x = 0, width = mc_gol_board_width(board); x < width; x++) {
//       printf("%c", alive_dead_display[mc_gol_board_cell(board, x, y)]);
//     }
//     printf("\n");
//   }
// }

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(
      stderr, "SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  const int width = 800;
  const int height = 600;
  SDL_Window* window = SDL_CreateWindow(
    argv[0], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
    SDL_WINDOW_SHOWN);

  if (window == NULL) {
    fprintf(
      stderr, "Window could not be created. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer* renderer =
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    fprintf(
      stderr, "Renderer could not be created. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  mc_gol_board_t* board = mc_gol_create_board(40, 27);

  // gosper glider gun
  mc_gol_set_board_cell(board, 2, 5, true);
  mc_gol_set_board_cell(board, 2, 6, true);
  mc_gol_set_board_cell(board, 3, 5, true);
  mc_gol_set_board_cell(board, 3, 6, true);

  mc_gol_set_board_cell(board, 12, 5, true);
  mc_gol_set_board_cell(board, 12, 6, true);
  mc_gol_set_board_cell(board, 12, 7, true);
  mc_gol_set_board_cell(board, 13, 4, true);
  mc_gol_set_board_cell(board, 13, 8, true);
  mc_gol_set_board_cell(board, 14, 3, true);
  mc_gol_set_board_cell(board, 14, 9, true);
  mc_gol_set_board_cell(board, 15, 3, true);
  mc_gol_set_board_cell(board, 15, 9, true);
  mc_gol_set_board_cell(board, 16, 6, true);
  mc_gol_set_board_cell(board, 17, 4, true);
  mc_gol_set_board_cell(board, 17, 8, true);
  mc_gol_set_board_cell(board, 18, 5, true);
  mc_gol_set_board_cell(board, 18, 6, true);
  mc_gol_set_board_cell(board, 18, 7, true);
  mc_gol_set_board_cell(board, 19, 6, true);

  mc_gol_set_board_cell(board, 22, 3, true);
  mc_gol_set_board_cell(board, 22, 4, true);
  mc_gol_set_board_cell(board, 22, 5, true);
  mc_gol_set_board_cell(board, 23, 3, true);
  mc_gol_set_board_cell(board, 23, 4, true);
  mc_gol_set_board_cell(board, 23, 5, true);
  mc_gol_set_board_cell(board, 24, 2, true);
  mc_gol_set_board_cell(board, 24, 6, true);
  mc_gol_set_board_cell(board, 26, 1, true);
  mc_gol_set_board_cell(board, 26, 2, true);
  mc_gol_set_board_cell(board, 26, 6, true);
  mc_gol_set_board_cell(board, 26, 7, true);

  mc_gol_set_board_cell(board, 36, 3, true);
  mc_gol_set_board_cell(board, 36, 4, true);
  mc_gol_set_board_cell(board, 37, 3, true);
  mc_gol_set_board_cell(board, 37, 4, true);

  // eater
  mc_gol_set_board_cell(board, 27, 20, true);
  mc_gol_set_board_cell(board, 27, 21, true);
  mc_gol_set_board_cell(board, 28, 20, true);
  mc_gol_set_board_cell(board, 28, 21, true);

  mc_gol_set_board_cell(board, 32, 21, true);
  mc_gol_set_board_cell(board, 31, 22, true);
  mc_gol_set_board_cell(board, 33, 22, true);
  mc_gol_set_board_cell(board, 32, 23, true);

  mc_gol_set_board_cell(board, 34, 23, true);
  mc_gol_set_board_cell(board, 34, 24, true);
  mc_gol_set_board_cell(board, 34, 25, true);
  mc_gol_set_board_cell(board, 35, 25, true);

  const float aspect_ratio = (float)width / (float)(height);
  const as_mat44f orthographic_projection =
    as_mat44f_orthographic_projection_depth_zero_to_one_lh(
      -100.0f * aspect_ratio, 100.0f * aspect_ratio, -100.0f, 100.0f, 0.0f,
      1.0f);

  // for (;;) {
  //   const double delay = 0.1; // wait for 1/10th of a second
  //   const tick_t time = timer_current();
  //   printf("\33[H\33[2J\33[3J");
  //   print_board(board);
  //   mc_gol_update_board(board);
  //   while (timer_elapsed(time) < delay) {
  //     // busy wait (ideally cross-platform sleep for some of this...)
  //   }
  // }

  for (bool running = true; running;) {
    for (SDL_Event current_event; SDL_PollEvent(&current_event) != 0;) {
      if (current_event.type == SDL_QUIT) {
        running = false;
        break;
      }
    }

    // camera (0, 0, 0)

    // clear screen
    SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
    SDL_RenderClear(renderer);

    {
      as_point3f begin = (as_point3f){.x = -50.0f, .y = 0.0f};
      as_point3f end = (as_point3f){.x = 50.0f, .y = 0.0f};

      as_point4f ndc_begin = as_mat44f_mul_point4f(
        &orthographic_projection, as_point4f_from_point3f(begin));
      as_point4f ndc_end = as_mat44f_mul_point4f(
        &orthographic_projection, as_point4f_from_point3f(end));

      as_vec2f screen_begin =
        as_vec2f_from_point2f(as_point2f_from_point4f(ndc_begin));
      as_vec2f screen_end =
        as_vec2f_from_point2f(as_point2f_from_point4f(ndc_end));

      screen_begin = as_vec2f_add_vec2f(
        as_vec2f_mul_float(screen_begin, 0.5f),
        (as_vec2f){.x = 0.5f, .y = 0.5f});
      screen_begin.x *= width;
      screen_begin.y *= height;

      screen_end = as_vec2f_add_vec2f(
        as_vec2f_mul_float(screen_end, 0.5f), (as_vec2f){.x = 0.5f, .y = 0.5f});
      screen_end.x *= width;
      screen_end.y *= height;

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderDrawLine(
        renderer, screen_begin.x, screen_begin.y, screen_end.x, screen_end.y);
    }

    {
      as_point3f begin = (as_point3f){.x = 0.0f, .y = -50.0f};
      as_point3f end = (as_point3f){.x = 0.0f, .y = 50.0f};

      as_point4f ndc_begin = as_mat44f_mul_point4f(
        &orthographic_projection, as_point4f_from_point3f(begin));
      as_point4f ndc_end = as_mat44f_mul_point4f(
        &orthographic_projection, as_point4f_from_point3f(end));

      as_vec2f screen_begin =
        as_vec2f_from_point2f(as_point2f_from_point4f(ndc_begin));
      as_vec2f screen_end =
        as_vec2f_from_point2f(as_point2f_from_point4f(ndc_end));

      screen_begin = as_vec2f_add_vec2f(
        as_vec2f_mul_float(screen_begin, 0.5f),
        (as_vec2f){.x = 0.5f, .y = 0.5f});
      screen_begin.x *= width;
      screen_begin.y *= height;

      screen_end = as_vec2f_add_vec2f(
        as_vec2f_mul_float(screen_end, 0.5f), (as_vec2f){.x = 0.5f, .y = 0.5f});
      screen_end.x *= width;
      screen_end.y *= height;

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderDrawLine(
        renderer, screen_begin.x, screen_begin.y, screen_end.x, screen_end.y);
    }

    SDL_RenderPresent(renderer);
  }

  mc_gol_destroy_board(board);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
