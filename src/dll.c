
#include"dll.h"

vec2 bread_math_add_v2(vec2 a, vec2 b) {
  vec2 result = {
    .x = a.x + b.x,
    .y = a.y + b.y
  };
  return result;
}

vec2 bread_math_add_r4(vec2 a, float b) {
  vec2 result = {
    .x = a.x + b,
    .y = a.y + b
  };
  return result;
}

vec2 bread_math_mul_r4(vec2 a, float b) {
  vec2 result = {
    .x = a.x * b,
    .y = a.y * b
  };
  return result;
}

float bread_math_dot(vec2 a, vec2 b) {
  return a.x*b.x + a.y*b.y;
}

#include<math.h>
float bread_math_len(vec2 a) {
  return sqrtf(a.x*a.x + a.y*a.y);
}

vec2 bread_math_normalof(vec2 a) {
  return bread_math_mul_r4(a, 1.0 / bread_math_len(a));
}

__declspec(dllexport) void load(t_bread_math *lib) {
  lib->add_v2 = (void *)(&bread_math_add_v2);
  lib->add_r4 = (void *)(&bread_math_add_r4);
  lib->mul_r4 = (void *)(&bread_math_mul_r4);
  lib->dot = (void *)(&bread_math_dot);
  lib->len = (void *)(&bread_math_len);
  lib->normalof = (void *)(&bread_math_normalof);
}
