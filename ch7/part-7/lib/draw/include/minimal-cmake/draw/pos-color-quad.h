#ifndef POS_COL_QUAD_H
#define POS_COL_QUAD_H

#include "mc_draw_export.h"

#include <as-types.h>
#include <bgfx/c99/bgfx.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct color4f_t {
  float r;
  float g;
  float b;
  float a;
} color4f_t;

typedef struct pos_color_quad_t {
  as_vec3f position;
  color4f_t color;
} pos_color_quad_t;

typedef struct pos_color_quads_t pos_color_quads_t;

MC_DRAW_EXPORT pos_color_quads_t* create_pos_color_quads(
  const bgfx_vertex_layout_t* vertex_layout);
MC_DRAW_EXPORT void destroy_pos_color_quads(pos_color_quads_t* pos_color_quads);

MC_DRAW_EXPORT void pos_color_quads_set_render_context(
  pos_color_quads_t* pos_color_quads, bgfx_view_id_t view_id,
  bgfx_program_handle_t program_handle, bgfx_uniform_handle_t color_uniform);

MC_DRAW_EXPORT void pos_color_quads_add_quad(
  pos_color_quads_t* pos_color_quads, pos_color_quad_t quad);
MC_DRAW_EXPORT void pos_color_quads_submit(pos_color_quads_t* pos_color_quads);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // POS_COL_QUAD_H
