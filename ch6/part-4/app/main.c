// third-party dependencies
#include <as-ops.h>
#include <bgfx/c99/bgfx.h>
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

typedef struct color_t {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} color_t;

double seconds_elapsed(
  const uint64_t previous_counter, const uint64_t current_counter) {
  return (double)(current_counter - previous_counter)
       / (double)SDL_GetPerformanceFrequency();
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(
      stderr, "SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  const as_vec2i screen_dimensions = (as_vec2i){.x = 800, .y = 600};
  SDL_Window* window = SDL_CreateWindow(
    argv[0], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    screen_dimensions.x, screen_dimensions.y, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    fprintf(
      stderr, "Window could not be created. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_SysWMinfo wmi;
  SDL_VERSION(&wmi.version);
  if (!SDL_GetWindowWMInfo(window, &wmi)) {
    fprintf(
      stderr, "SDL_SysWMinfo could not be retrieved. SDL_Error: %s\n",
      SDL_GetError());
    return 1;
  }
  bgfx_render_frame(-1); // single threaded mode

  bgfx_platform_data_t pd = {};
#if BX_PLATFORM_WINDOWS
  pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_OSX
  pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_LINUX
  pd.ndt = wmi.info.x11.display;
  pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
#endif

  bgfx_init_t bgfx;
  bgfx_init_ctor(&bgfx);
  bgfx.type = BGFX_RENDERER_TYPE_COUNT; // auto choose renderer
  bgfx.resolution.width = screen_dimensions.x;
  bgfx.resolution.height = screen_dimensions.y;
  bgfx.resolution.reset = BGFX_RESET_VSYNC;
  bgfx.platformData = pd;
  bgfx_init(&bgfx);

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

  double timer = 0.0;
  const double delay = 0.1f;
  double previous_frame_time = SDL_GetPerformanceFrequency();
  for (bool running = true; running;) {
    for (SDL_Event current_event; SDL_PollEvent(&current_event) != 0;) {
      if (current_event.type == SDL_QUIT) {
        running = false;
        break;
      }
    }

    const int64_t current_counter = SDL_GetPerformanceCounter();
    const double delta_time =
      seconds_elapsed(previous_frame_time, current_counter);
    previous_frame_time = current_counter;

    timer += delta_time;

    // clear screen
    bgfx_set_view_clear(
      0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x6495EDFF, 1.0f, 0);
    bgfx_set_view_rect(0, 0, 0, screen_dimensions.x, screen_dimensions.y);

    const float cell_size = 15;
    const as_point2i board_top_left_corner = (as_point2i){
      .x = (screen_dimensions.x / 2)
         - (mc_gol_board_width(board) * cell_size) * 0.5f,
      .y = (screen_dimensions.y / 2)
         - (mc_gol_board_height(board) * cell_size) * 0.5f};
    for (int32_t y = 0, height = mc_gol_board_height(board); y < height; y++) {
      for (int32_t x = 0, width = mc_gol_board_width(board); x < width; x++) {
        const as_point2i cell_position = as_point2i_add_vec2i(
          board_top_left_corner,
          (as_vec2i){.x = x * cell_size, .y = y * cell_size});
        const color_t cell_color =
          mc_gol_board_cell(board, x, y)
            ? (color_t){.r = 255, .g = 255, .b = 255, .a = 255}
            : (color_t){.a = 255};
        // SDL_SetRenderDrawColor(
        //   renderer, cell_color.r, cell_color.g, cell_color.b, cell_color.a);
        const SDL_Rect cell = (SDL_Rect){
          .x = cell_position.x,
          .y = cell_position.y,
          .w = cell_size,
          .h = cell_size};
        // SDL_RenderFillRect(renderer, &cell);
      }
    }

    if (timer > delay) {
      mc_gol_update_board(board);
      timer = 0.0;
    }

    // SDL_RenderPresent(renderer);
    bgfx_touch(0);
    bgfx_frame(false);
  }

  mc_gol_destroy_board(board);

  bgfx_shutdown();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
