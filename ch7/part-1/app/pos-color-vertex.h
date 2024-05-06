#ifndef POS_COL_VERT_H
#define POS_COL_VERT_H

#include <as-types.h>

#include <stdint.h>

typedef struct bgfx_vertex_layout_s bgfx_vertex_layout_t;
typedef enum bgfx_renderer_type bgfx_renderer_type_t;

typedef struct pos_color_vertex_t {
  as_vec3f pos;
  uint32_t abgr;
} pos_color_vertex_t;

bgfx_vertex_layout_t create_pos_col_vert_layout(
  bgfx_renderer_type_t renderer_type);

#endif // POS_COL_VERT_H
