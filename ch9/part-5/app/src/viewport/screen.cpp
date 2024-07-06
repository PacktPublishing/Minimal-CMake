#include "screen.h"

#include <as-ops.h>

as_point2f screen_from_world(
  const as_point2f world_position, const as_mat44f* orthographic_projection,
  const as_vec2i screen_dimensions) {
  const as_point2f ndc_position_minus_one_to_one =
    as_point2f_from_point4f(as_mat44f_mul_point4f(
      orthographic_projection, as_point4f_from_point2f(world_position)));
  const as_point2f ndc_position_zero_to_one =
    as_point2f_from_vec2f(as_vec2f_add_vec2f(
      as_vec2f_mul_float(
        as_vec2f_from_point2f(ndc_position_minus_one_to_one), 0.5f),
      as_vec2f{0.5f, 0.5f}));
  return as_point2f{
    .x = ndc_position_zero_to_one.x * screen_dimensions.x,
    .y = ndc_position_zero_to_one.y * screen_dimensions.y};
}

as_point3f world_from_screen(
  const as_point2i screen_position, const as_mat44f* orthographic_projection,
  const as_vec2i screen_dimensions) {
  const as_point2f ndc_position_zero_to_one = as_point2f{
    .x = (float)screen_position.x / (float)screen_dimensions.x,
    .y = (float)screen_position.y / screen_dimensions.y};
  const as_point2f ndc_position_minus_one_to_one =
    as_point2f_from_vec2f(as_vec2f_mul_float(
      as_vec2f_sub_vec2f(
        as_vec2f_from_point2f(ndc_position_zero_to_one), as_vec2f{0.5f, 0.5f}),
      2.0f));
  const as_point4f world_position = as_mat44f_mul_point4f_v(
    as_mat44f_inverse(orthographic_projection),
    as_point4f_from_point2f(ndc_position_minus_one_to_one));
  return as_point3f{
    .x = world_position.x, .y = world_position.y, .z = world_position.z};
}
