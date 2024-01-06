#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void* internal_array_reserve(void* array, int new_cap, int elem_size);
void* internal_array_resize(void* array, int count, int elem_size);
void* internal_array_grow(void* array, int elem_size);

#define array_resize(array, count)                                             \
  do {                                                                         \
    (array) = internal_array_resize((array), count, sizeof(*(array)));         \
  } while (0);

#define array_reserve(array, new_cap)                                          \
  do {                                                                         \
    (array) = internal_array_reserve((array), new_cap, sizeof(*(array)));      \
  } while (0);

#define array_push(array, value)                                               \
  do {                                                                         \
    (array) = internal_array_grow((array), sizeof(*(array)));                  \
    (array)[array_size(array) - 1] = (value);                                  \
  } while (0);

void array_pop(void* array);
int array_size(void* array);
int array_capacity(void* array);
bool array_empty(void* array);
void array_free(void* array);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ARRAY_H
