#include<stdio.h>

#include"dll.h"
t_bread_math static *math;

int main(void) {
  
  // load library interface from dll
  if(!bread__load_lib(&math, "math.dll")) {
    printf("wrong version of DLL or DLL not found!\n");
    return 1;
  }
  
  // use the library
  vec2 right = {1.0f, 0.0f};
  vec2 up = {0.0f, 1.0f};
  vec2 diag = math->add_v2(right, up);
  float dot = math->dot(diag, up);
  up = math->mul_r4(up, dot);
  
  return 0;
}
