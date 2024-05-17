#include "minimal-cmake/draw/pos-color-quad.h"

#include "minimal-cmake/draw/pos-color-vertex.h"

#include <as-ops.h>
#include <bgfx/c99/bgfx.h>
#include <minimal-cmake/array.h>

#include <string.h>

typedef struct pos_color_quads_t {
  uint64_t state;
  bgfx_view_id_t view;
  pos_color_quad_t* quads;
  bgfx_vertex_layout_t layout;
  bgfx_vertex_buffer_handle_t vertex_buffer;
  bgfx_index_buffer_handle_t index_buffer;
  bgfx_program_handle_t program_handle;
  bgfx_uniform_handle_t color_uniform;
} pos_color_quads_t;

static pos_color_vertex_t quad_vertices[] = {
  {(as_vec3f){-0.5f, -0.5f, 0.0f}, 0xffffffff},
  {(as_vec3f){0.5f, -0.5f, 0.0f}, 0xffffffff},
  {(as_vec3f){-0.5f, 0.5f, 0.0f}, 0xffffffff},
  {(as_vec3f){0.5f, 0.5f, 0.0f}, 0xffffffff}};
static const uint16_t quad_indices[] = {0, 1, 2, 1, 3, 2};

pos_color_quads_t* create_pos_color_quads(
  const bgfx_vertex_layout_t* vertex_layout) {
  pos_color_quads_t* pos_color_quads = malloc(sizeof(*pos_color_quads));
  *pos_color_quads = (pos_color_quads_t){};
  pos_color_quads->vertex_buffer = bgfx_create_vertex_buffer(
    bgfx_make_ref(quad_vertices, sizeof(quad_vertices)), vertex_layout, 0);
  pos_color_quads->index_buffer = bgfx_create_index_buffer(
    bgfx_make_ref(quad_indices, sizeof(quad_indices)), 0);
  return pos_color_quads;
}

void destroy_pos_color_quads(pos_color_quads_t* pos_color_quads) {
  bgfx_destroy_index_buffer(pos_color_quads->index_buffer);
  bgfx_destroy_vertex_buffer(pos_color_quads->vertex_buffer);
  mc_array_free(pos_color_quads->quads);
  free(pos_color_quads);
}

void pos_color_quads_set_render_context(
  pos_color_quads_t* pos_color_quads, const bgfx_view_id_t view_id,
  const bgfx_program_handle_t program_handle,
  const bgfx_uniform_handle_t color_uniform) {
  pos_color_quads->view = view_id;
  pos_color_quads->program_handle = program_handle;
  pos_color_quads->color_uniform = color_uniform;
}

void pos_color_quads_add_quad(
  pos_color_quads_t* pos_color_quads, pos_color_quad_t quad) {
  mc_array_push(pos_color_quads->quads, quad);
}

void pos_color_quads_submit(pos_color_quads_t* pos_color_quads) {
  for (int32_t quad = 0, quad_count = mc_array_size(pos_color_quads->quads);
       quad < quad_count; quad++) {
    const as_mat44f transform = as_mat44f_transpose_v(
      as_mat44f_translation_from_vec3f(pos_color_quads->quads[quad].position));
    bgfx_set_transform(transform.elem, 1);
    bgfx_set_vertex_buffer(0, pos_color_quads->vertex_buffer, 0, 4);
    bgfx_set_index_buffer(pos_color_quads->index_buffer, 0, 6);
    const float color[4] = {
      pos_color_quads->quads[quad].color.r,
      pos_color_quads->quads[quad].color.g,
      pos_color_quads->quads[quad].color.b,
      pos_color_quads->quads[quad].color.a};
    bgfx_set_uniform(pos_color_quads->color_uniform, color, 1);
    bgfx_submit(0, pos_color_quads->program_handle, 0, BGFX_DISCARD_ALL);
  }
  mc_array_resize(pos_color_quads->quads, 0);
}
