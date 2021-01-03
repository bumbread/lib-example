/* date = January 3rd 2021 1:29 pm */

#ifndef DLL_H
#define DLL_H

struct {
  float x;
  float y;
} typedef vec2;

struct {
  vec2 (*add_v2)(vec2,vec2);
  vec2 (*add_r4)(vec2,float);
  vec2 (*mul_r4)(vec2,float);
  float (*dot)(vec2,vec2);
  float (*len)(vec2);
  vec2 (*normalof)(vec2);
} typedef t_bread_math;

#ifdef __linux__ 
// TODO(bumbread): linux code
#elif _WIN32
// bread__load_lib version for windows
#pragma comment(lib, "user32.lib")
#include<Windows.h>
void bread__load_lib(t_bread_math *lib, char *dll_name) {
  HMODULE libraryHandle = LoadLibraryA(dll_name);
  void (*load)(t_bread_math *) = (void *)GetProcAddress(libraryHandle, "load");
  load(lib);
}
#endif

#endif //DLL_H
