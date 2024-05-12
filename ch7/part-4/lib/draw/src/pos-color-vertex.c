#include "minimal-cmake/draw/pos-color-vertex.h"

#include <bgfx/c99/bgfx.h>

bgfx_vertex_layout_t create_pos_col_vert_layout(
  const bgfx_renderer_type_t renderer_type) {
  bgfx_vertex_layout_t pos_col_vert_layout;
  bgfx_vertex_layout_begin(&pos_col_vert_layout, renderer_type);
  bgfx_vertex_layout_add(
    &pos_col_vert_layout, BGFX_ATTRIB_POSITION, 3, BGFX_ATTRIB_TYPE_FLOAT,
    false, false);
  bgfx_vertex_layout_add(
    &pos_col_vert_layout, BGFX_ATTRIB_COLOR0, 4, BGFX_ATTRIB_TYPE_UINT8, true,
    false);
  bgfx_vertex_layout_end(&pos_col_vert_layout);
  return pos_col_vert_layout;
}
