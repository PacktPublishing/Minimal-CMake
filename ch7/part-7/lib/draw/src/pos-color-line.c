#include "minimal-cmake/draw/pos-color-line.h"

#include <as-ops.h>
#include <bgfx/c99/bgfx.h>
#include <minimal-cmake/array.h>

#include <string.h>

typedef struct pos_color_lines_t {
  uint64_t state;
  bgfx_view_id_t view;
  pos_color_line_t* lines;
  bgfx_vertex_layout_t layout;
  bgfx_program_handle_t program_handle;
  bgfx_uniform_handle_t color_uniform;
} pos_color_lines_t;

pos_color_lines_t* create_pos_color_lines(void) {
  pos_color_lines_t* pos_color_lines = malloc(sizeof(*pos_color_lines));
  *pos_color_lines = (pos_color_lines_t){0};
  pos_color_lines->state = BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA
                         | BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA;
  return pos_color_lines;
}

void destroy_pos_color_lines(pos_color_lines_t* pos_color_lines) {
  mc_array_free(pos_color_lines->lines);
  free(pos_color_lines);
}

void pos_color_lines_set_render_context(
  pos_color_lines_t* pos_color_lines, const bgfx_view_id_t view,
  const bgfx_program_handle_t program_handle,
  const bgfx_vertex_layout_t* vertex_layout,
  const bgfx_uniform_handle_t color_uniform) {
  pos_color_lines->view = view;
  pos_color_lines->layout = *vertex_layout;
  pos_color_lines->color_uniform = color_uniform;
  pos_color_lines->program_handle = program_handle;
}

void pos_color_lines_add_line(
  pos_color_lines_t* pos_color_lines, const pos_color_line_t line) {
  mc_array_push(pos_color_lines->lines, line);
}

void pos_color_lines_submit(pos_color_lines_t* pos_color_lines) {
  const int32_t requested_vertex_count =
    mc_array_size(pos_color_lines->lines) * 2;
  if (requested_vertex_count == 0) {
    return;
  }

  const uint32_t available_vertex_count =
    bgfx_get_avail_transient_vertex_buffer(
      requested_vertex_count, &pos_color_lines->layout);

  if (available_vertex_count != requested_vertex_count) {
    return;
  }

  bgfx_transient_vertex_buffer_t line_tvb;
  bgfx_alloc_transient_vertex_buffer(
    &line_tvb, requested_vertex_count, &pos_color_lines->layout);

  memcpy(
    line_tvb.data, pos_color_lines->lines,
    pos_color_lines->layout.stride * requested_vertex_count);

  const as_mat44f identity = as_mat44f_identity();
  bgfx_set_transform(identity.elem, 1);

  bgfx_set_state(pos_color_lines->state, 0);

  bgfx_set_transient_vertex_buffer(0, &line_tvb, 0, requested_vertex_count);
  const float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  bgfx_set_uniform(pos_color_lines->color_uniform, color, 1);
  bgfx_submit(
    pos_color_lines->view, pos_color_lines->program_handle, 0,
    BGFX_DISCARD_ALL);

  mc_array_resize(pos_color_lines->lines, 0);
}
