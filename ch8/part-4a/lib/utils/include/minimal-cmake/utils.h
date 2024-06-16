#ifndef MC_UTILS_H
#define MC_UTILS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

static int32_t mc_try_wrap(const int32_t index, const int32_t dim) {
  return ((index % dim) + dim) % dim;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MC_UTILS_H
