#ifndef AS_TYPES_MATH_H
#define AS_TYPES_MATH_H

typedef struct as_vec2f {
  float x;
  float y;
} as_vec2f;

typedef struct as_vec3f {
  float x;
  float y;
  float z;
} as_vec3f;

typedef struct as_vec2i {
  int x;
  int y;
} as_vec2i;

typedef struct as_vec3i {
  int x;
  int y;
  int z;
} as_vec3i;

typedef struct as_point2f {
  float x;
  float y;
} as_point2f;

typedef struct as_point3f {
  float x;
  float y;
  float z;
} as_point3f;

typedef struct as_point4f {
  float x;
  float y;
  float z;
  float w;
} as_point4f;

typedef struct as_point2i {
  int x;
  int y;
} as_point2i;

typedef struct as_size2i {
  int width;
  int height;
} as_size2i;

typedef struct as_rect {
  as_point2i pos;
  as_size2i size;
} as_rect;

typedef struct as_mat22f {
  float elem[4];
} as_mat22f;

typedef struct as_mat33f {
  float elem[9];
} as_mat33f;

typedef struct as_mat44f {
  float elem[16];
} as_mat44f;

typedef struct as_mat34f {
  float elem[12];
} as_mat34f;

typedef struct as_plane {
  as_point3f point;
  as_vec3f normal;
} as_plane;

typedef struct as_quat {
  float w;
  float x;
  float y;
  float z;
} as_quat;

#endif // AS_TYPES_MATH_H
