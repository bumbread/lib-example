/* date = January 3rd 2021 1:29 pm */

#ifndef DLL_H
#define DLL_H

/* if update introduces incompatible changes to an interface, this number is increased */
#define BREAD_LIBRARY_MAJOR 1
/* if an update _adds_ functionality in compatible way, this number is increased*/
#define BREAD_LIBRARY_MINOR 1

/* library introduced types */
struct {
  float x;
  float y;
} typedef vec2;

/* pointer table that defines library interface */
struct {
  unsigned expected_version;
  vec2 (*add_v2)(vec2,vec2);
  vec2 (*add_r4)(vec2,float);
  vec2 (*mul_r4)(vec2,float);
  float (*dot)(vec2,vec2);
  float (*len)(vec2);
  vec2 (*normalof)(vec2);
  // t_bread_lib_ptable declares internal pointer table for the interface, 
  // t_bread_math declares user-facing library interface abstraction
} typedef t_bread_math;

/* library loader */
#ifdef __linux__ 
// linux code will go here.
#elif _WIN32
// function responsible for loading the .dll file
// and calling into internal loader of the library.
#include<Windows.h>
#pragma comment(lib, "user32.lib")
int bread__load_lib(t_bread_math **lib, char *dll_name) {
  HMODULE libraryHandle = LoadLibraryA(dll_name);
  if(!libraryHandle) return 0;
  int (*load)(t_bread_math **, unsigned) = (void *)GetProcAddress(libraryHandle, "load");
  if(!load) return 0;
  return load(lib, BREAD_LIBRARY_MAJOR);
}
#endif

#endif //DLL_H
