#include "minimal-cmake/array.h"

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_RAW_DATA(array) ((int*)(array)-2)
#define ARRAY_CAPACITY(array) (ARRAY_RAW_DATA(array)[0])
#define ARRAY_SIZE(array) (ARRAY_RAW_DATA(array)[1])

void* internal_array_reserve(
  void* array, const int new_cap, const int elem_size) {
  if (array == NULL) {
    const int raw_size = sizeof(int) * 2 + elem_size * new_cap;
    int* base = malloc(raw_size);
    base[0] = new_cap; // capacity
    base[1] = 0; // occupied
    return base + 2;
  } else if (new_cap > ARRAY_CAPACITY(array)) {
    const int size = ARRAY_SIZE(array);
    const int raw_size = sizeof(int) * 2 + elem_size * new_cap;
    int* base = realloc(ARRAY_RAW_DATA(array), raw_size);
    base[0] = new_cap;
    base[1] = size;
    return base + 2;
  } else {
    return array;
  }
}

void* internal_array_resize(void* array, const int count, const int elem_size) {
  array = internal_array_reserve(array, count, elem_size);
  ARRAY_SIZE(array) = count;
  return array;
}

static int max_int(const int lhs, const int rhs) {
  return lhs > rhs ? lhs : rhs;
}

void* internal_array_grow(void* array, int elem_size) {
  const int capacity = array_capacity(array);
  if (array_size(array) == capacity) {
    array = internal_array_reserve(array, max_int(capacity * 2, 1), elem_size);
  }
  ARRAY_SIZE(array) += 1;
  return array;
}

void array_pop(void* array) {
  if (array_size(array) >= 1) {
    ARRAY_SIZE(array) -= 1;
  }
}

int array_size(void* array) {
  return (array != NULL) ? (ARRAY_SIZE(array)) : 0;
}

int array_capacity(void* array) {
  return (array != NULL) ? (ARRAY_CAPACITY(array)) : 0;
}

bool array_empty(void* array) {
  return array_size(array) == 0;
}

void array_free(void* array) {
  if (array != NULL) {
    free(ARRAY_RAW_DATA(array));
  }
}
