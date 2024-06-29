#include <as-types.h>

as_point2f screen_from_world(
  const as_point2f world_position, const as_mat44f* orthographic_projection,
  const as_vec2i screen_dimensions);

as_point3f world_from_screen(
  const as_point2i screen_position, const as_mat44f* orthographic_projection,
  const as_vec2i screen_dimensions);
