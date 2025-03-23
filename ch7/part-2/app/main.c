// third-party dependencies
#include <SDL.h>
#include <SDL_syswm.h>
#include <as-ops.h>
#include <bgfx/c99/bgfx.h>
#include <minimal-cmake-gol/gol.h>
#include <minimal-cmake/array.h>

// system includes
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct color4f_t {
  float r;
  float g;
  float b;
  float a;
} color4f_t;

typedef struct pos_color_vertex_t {
  float x;
  float y;
  float z;
  uint32_t abgr;
} pos_color_vertex_t;

static pos_color_vertex_t quad_vertices[] = {
  {-0.5f, -0.5f, 0.0f, 0xffffffff},
  {0.5f, -0.5f, 0.0f, 0xffffffff},
  {-0.5f, 0.5f, 0.0f, 0xffffffff},
  {0.5f, 0.5f, 0.0f, 0xffffffff}};
static const uint16_t quad_indices[] = {0, 1, 2, 1, 3, 2};

static char* read_file(const char* filepath) {
  FILE* file = fopen(filepath, "rb");
  if (file == NULL) {
    return NULL;
  }
  // seek to end of file
  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    return NULL;
  }
  // find length of file
  const int64_t file_size = ftell(file);
  if (file_size == -1) {
    fclose(file);
    return NULL;
  }
  // return to beginning of file
  if (fseek(file, 0, SEEK_SET) != 0) {
    fclose(file);
    return NULL;
  }
  // allocate buffer to hold contents of file
  char* buffer = NULL;
  mc_array_resize(buffer, file_size);
  // read file
  const size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
  if (bytes_read == 0) {
    fclose(file);
    mc_array_free(buffer);
    return NULL;
  }
  fclose(file);
  // return array buffer (remember to deallocate after)
  return buffer;
}

static bgfx_shader_handle_t create_shader(
  const char* shader, const int size, const char* name) {
  const bgfx_memory_t* mem = bgfx_copy(shader, size);
  const bgfx_shader_handle_t handle = bgfx_create_shader(mem);
  bgfx_set_shader_name(handle, name, strlen(name));
  return handle;
}

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

  bgfx_renderer_type_t renderer_type = BGFX_RENDERER_TYPE_COUNT;
  bgfx_platform_data_t pd = {0};
#if BX_PLATFORM_WINDOWS
  pd.nwh = wmi.info.win.window;
  renderer_type = BGFX_RENDERER_TYPE_DIRECT3D11;
#elif BX_PLATFORM_OSX
  pd.nwh = wmi.info.cocoa.window;
  renderer_type = BGFX_RENDERER_TYPE_METAL;
#elif BX_PLATFORM_LINUX
  pd.ndt = wmi.info.x11.display;
  pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
  renderer_type = BGFX_RENDERER_TYPE_OPENGL;
#endif

  bgfx_init_t bgfx;
  bgfx_init_ctor(&bgfx);
  bgfx.type = renderer_type;
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

  bgfx_vertex_layout_t pos_col_vert_layout;
  bgfx_vertex_layout_begin(&pos_col_vert_layout, renderer_type);
  bgfx_vertex_layout_add(
    &pos_col_vert_layout, BGFX_ATTRIB_POSITION, 3, BGFX_ATTRIB_TYPE_FLOAT,
    false, false);
  bgfx_vertex_layout_add(
    &pos_col_vert_layout, BGFX_ATTRIB_COLOR0, 4, BGFX_ATTRIB_TYPE_UINT8, true,
    false);
  bgfx_vertex_layout_end(&pos_col_vert_layout);

  const bgfx_vertex_buffer_handle_t vertex_buffer = bgfx_create_vertex_buffer(
    bgfx_make_ref(quad_vertices, sizeof(quad_vertices)), &pos_col_vert_layout,
    0);
  const bgfx_index_buffer_handle_t index_buffer = bgfx_create_index_buffer(
    bgfx_make_ref(quad_indices, sizeof(quad_indices)), 0);

  char* vs_shader = read_file("shader/build/vs_vertcol.bin");
  char* fs_shader = read_file("shader/build/fs_vertcol.bin");
  if (!vs_shader || !fs_shader) {
    fprintf(
      stderr, "Shaders not found. Have you built them using "
              "compile-shader-<platform>.sh/bat script?\n");
    return 1;
  }

  const bgfx_shader_handle_t vertex_shader =
    create_shader(vs_shader, mc_array_size(vs_shader), "vs_shader");
  const bgfx_shader_handle_t fragment_shader =
    create_shader(fs_shader, mc_array_size(fs_shader), "fs_shader");
  const bgfx_program_handle_t program =
    bgfx_create_program(vertex_shader, fragment_shader, true);

  mc_array_free(vs_shader);
  mc_array_free(fs_shader);

  const bgfx_uniform_handle_t u_color =
    bgfx_create_uniform("u_color", BGFX_UNIFORM_TYPE_VEC4, 1);

  double timer = 0.0;
  const double delay = 0.1;
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
      0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xf2f2f2ff, 1.0f, 0);
    bgfx_set_view_rect(0, 0, 0, screen_dimensions.x, screen_dimensions.y);

    const float zoom = 20.0f;
    const as_mat44f identity = as_mat44f_identity();

    const float aspect_ratio =
      (float)screen_dimensions.x / (float)screen_dimensions.y;
    const as_mat44f orthographic_projection =
      as_mat44f_orthographic_projection_depth_zero_to_one_lh(
        -zoom * aspect_ratio, zoom * aspect_ratio, -zoom, zoom, 0.0f, 1.0f);
    bgfx_set_view_transform(0, identity.elem, orthographic_projection.elem);

    const as_vec3f board_top_left_corner = (as_vec3f){
      .x = (-mc_gol_board_width(board) * 0.5f) + 0.5f,
      .y = (mc_gol_board_height(board) * 0.5f) - 0.5f};
    for (int32_t y = 0, height = mc_gol_board_height(board); y < height; y++) {
      for (int32_t x = 0, width = mc_gol_board_width(board); x < width; x++) {
        const color4f_t cell_color =
          mc_gol_board_cell(board, x, y)
            ? (color4f_t){.r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f}
            : (color4f_t){.a = 1.0f};
        const as_mat44f transform = as_mat44f_transpose_v(
          as_mat44f_translation_from_vec3f(as_vec3f_add_vec3f(
            board_top_left_corner, (as_vec3f){.x = x, .y = -y})));
        bgfx_set_transform(transform.elem, 1);
        bgfx_set_vertex_buffer(0, vertex_buffer, 0, 4);
        bgfx_set_index_buffer(index_buffer, 0, 6);
        const float color[4] = {
          cell_color.r, cell_color.g, cell_color.b, cell_color.a};
        bgfx_set_uniform(u_color, color, 1);
        bgfx_submit(0, program, 0, BGFX_DISCARD_ALL);
      }
    }

    if (timer > delay) {
      mc_gol_update_board(board);
      timer = 0.0;
    }

    bgfx_touch(0);
    bgfx_frame(false);
  }

  bgfx_destroy_uniform(u_color);
  bgfx_destroy_program(program);
  bgfx_destroy_index_buffer(index_buffer);
  bgfx_destroy_vertex_buffer(vertex_buffer);

  mc_gol_destroy_board(board);

  bgfx_shutdown();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
