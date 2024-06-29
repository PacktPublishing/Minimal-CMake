#include <as-ops.h>
#include <catch2/catch_test_macros.hpp>

#include "screen.h"

TEST_CASE("screen from world") {
  const float zoom = 20.0f;
  const float aspect_ratio = 16.0f / 9.0f;
  const as_mat44f orthographic_projection =
    as_mat44f_orthographic_projection_depth_zero_to_one_lh(
      -zoom * aspect_ratio, zoom * aspect_ratio, -zoom, zoom, 0.0f, 1.0f);
  const as_point2f screen =
    screen_from_world({0.0f, 0.0f}, &orthographic_projection, {1920, 1080});
  CHECK(as_point2f_near(screen, {960.0f, 540.0f}, 0.001f, 0.001f));
}

TEST_CASE("world from screen") {
  const float zoom = 20.0f;
  const float aspect_ratio = 16.0f / 9.0f;
  const as_mat44f orthographic_projection =
    as_mat44f_orthographic_projection_depth_zero_to_one_lh(
      -zoom * aspect_ratio, zoom * aspect_ratio, -zoom, zoom, 0.0f, 1.0f);
  const as_point3f world =
    world_from_screen({960, 540}, &orthographic_projection, {1920, 1080});
  CHECK(as_point3f_near(world, {0.0f, 0.0f, 0.0f}, 0.001f, 0.001f));
}

TEST_CASE("screen from world, world from screen") {
  const float zoom = 20.0f;
  const float aspect_ratio = 16.0f / 9.0f;
  const as_mat44f orthographic_projection =
    as_mat44f_orthographic_projection_depth_zero_to_one_lh(
      -zoom * aspect_ratio, zoom * aspect_ratio, -zoom, zoom, 0.0f, 1.0f);
  const as_point2f screen =
    screen_from_world({20.0f, -10.0f}, &orthographic_projection, {1920, 1080});
  const as_point3f world = world_from_screen(
    as_point2i_from_point2f(screen), &orthographic_projection, {1920, 1080});
  CHECK(as_point3f_near(world, {20.0f, -10.0f, 0.0f}, 0.001f, 0.001f));
}

TEST_CASE("world from screen, screen from world") {
  const float zoom = 20.0f;
  const float aspect_ratio = 16.0f / 9.0f;
  const as_mat44f orthographic_projection =
    as_mat44f_orthographic_projection_depth_zero_to_one_lh(
      -zoom * aspect_ratio, zoom * aspect_ratio, -zoom, zoom, 0.0f, 1.0f);
  const as_point3f world =
    world_from_screen({56, 247}, &orthographic_projection, {1920, 1080});
  const as_point2f screen = screen_from_world(
    as_point2f{world.x, world.y}, &orthographic_projection, {1920, 1080});
  CHECK(as_point2f_near(screen, {56.0f, 247.0f}, 0.001f, 0.001f));
}
