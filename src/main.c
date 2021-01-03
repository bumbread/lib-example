#include<stdio.h>

#include"dll.h"
int main(void) {
  printf("hi.\n");
  
  // dynamically load math library functions
  // into t_bread_math struct
  t_bread_math math;
  bread__load_lib(&math, "math.dll");
  
  // some testing
  vec2 right = {1.0f, 0.0f};
  vec2 up = {0.0f, 1.0f};
  vec2 diag = math.add_v2(right, up);
  float dot = math.dot(diag, up);
  up = math.mul_r4(up, dot);
  
  return 0;
}
