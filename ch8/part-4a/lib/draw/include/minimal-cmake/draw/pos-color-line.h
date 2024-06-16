#ifndef POS_COL_LINE_H
#define POS_COL_LINE_H

#include "mc_line_export.h"

#include "pos-color-vertex.h"

#include <bgfx/c99/bgfx.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct pos_color_line_t {
  pos_color_vertex_t begin;
  pos_color_vertex_t end;
} pos_color_line_t;

typedef struct pos_color_lines_t pos_color_lines_t;

MC_LINE_EXPORT pos_color_lines_t* create_pos_color_lines(void);
MC_LINE_EXPORT void destroy_pos_color_lines(pos_color_lines_t* pos_color_lines);

MC_LINE_EXPORT void pos_color_lines_set_render_context(
  pos_color_lines_t* pos_color_lines, bgfx_view_id_t view_id,
  bgfx_program_handle_t program_handle,
  const bgfx_vertex_layout_t* vertex_layout,
  bgfx_uniform_handle_t color_uniform);

MC_LINE_EXPORT void pos_color_lines_add_line(
  pos_color_lines_t* pos_color_lines, pos_color_line_t line);
MC_LINE_EXPORT void pos_color_lines_submit(pos_color_lines_t* pos_color_lines);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // POS_COL_LINE_H
