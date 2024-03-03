#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void* internal_mc_array_reserve(void* array, int new_cap, int elem_size);
void* internal_mc_array_resize(void* array, int count, int elem_size);
void* internal_mc_array_grow(void* array, int elem_size);

#define mc_array_resize(array, count)                                             \
  do {                                                                         \
    (array) = internal_mc_array_resize((array), count, sizeof(*(array)));         \
  } while (0);

#define mc_array_reserve(array, new_cap)                                          \
  do {                                                                         \
    (array) = internal_mc_array_reserve((array), new_cap, sizeof(*(array)));      \
  } while (0);

#define mc_array_push(array, value)                                               \
  do {                                                                         \
    (array) = internal_mc_array_grow((array), sizeof(*(array)));                  \
    (array)[mc_array_size(array) - 1] = (value);                                  \
  } while (0);

void mc_array_pop(void* array);
int mc_array_size(void* array);
int mc_array_capacity(void* array);
bool mc_array_empty(void* array);
void mc_array_free(void* array);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARRAY_H
