
#include"dll.h"

static vec2 add_v2(vec2 a, vec2 b) {
  vec2 result = {
    .x = a.x + b.x,
    .y = a.y + b.y
  };
  return result;
}

static vec2 add_r4(vec2 a, float b) {
  vec2 result = {
    .x = a.x + b,
    .y = a.y + b
  };
  return result;
}

static vec2 mul_r4(vec2 a, float b) {
  vec2 result = {
    .x = a.x * b,
    .y = a.y * b
  };
  return result;
}

static float dot(vec2 a, vec2 b) {
  return a.x*b.x + a.y*b.y;
}

#include<math.h>
float len(vec2 a) {
  return sqrtf(a.x*a.x + a.y*a.y);
}

vec2 normalof(vec2 a) {
  return mul_r4(a, 1.0 / len(a));
}

static t_bread_lib_ptable pointers = {
  .add_v2 = &add_v2,
  .add_r4 = &add_r4,
  .mul_r4 = &mul_r4,
  .dot = &dot,
  .len = &len,
  .normalof = &normalof,
};

__declspec(dllexport) int load(t_bread_math *lib, unsigned maj, unsigned min) {
  if(maj != BREAD_LIBRARY_MAJOR) return 0; // reject if incompatible
  if(min > BREAD_LIBRARY_MINOR) return 0; // reject if user expects functions that don't exist
  *lib = &pointers;
  return 1;
}