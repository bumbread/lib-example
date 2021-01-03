## Description

This is an example of implementing a basic library performing simple algebra on 2 dimansional vectors, implemented using one of my ideas. The library is structured in such a way as to compromize the uglyness of functions and significantly reduce the possibility of namespace collisions. Function "namespacing" is done by putting all the library declarations inside a library namespacing struct. In order to use a library the library header defines a function that fills the struct with pointers. It is possible that the library will have several such structs and therefore will have several initalization functions and several possible feature sets. The loader function is in the user's module and is included together with the library header. The loader function loads the library's loader function that is contained in the library's DLL module. The library's module function fills the struct with function pointers. 

The usage of the library could look like this:
```c
struct t_pref_library library;

user_code() {

    prefix_library_init(&library, "library.dll");
    
    library.callFunction1();
    library.doSomething("cat");

}

```

The function names are scoped as struct fields on one side and by module on another side. So there is no names leaking into the global scope of the user module. Additionally the struct to be filled with pointers is named by the user so it delegates the responsibility of managing name collisions to the user (and that managing is basically the same as managing variable names, isn't very hard).

## Advantages
- Reduces possible name collisions for functions while reducing extra typing
A library can contain tens, hundreds and thousands of functions. It is possible that one of them collides with another function with another library. Since C language doesn't have namespaces, the library developers have started to namespace functions by appending `LIBRARY_` to the function names. This doesn't guarantee that the functions won't collide but it significantly reduces the possibility of the collision.

However with my approach there *Isn't even a possibility* that the functions will collide. Since the functions are struct members and the struct members don't collide.

Of couse this approach doesn't guarantee that library types, library defines and the loader function won't collide. However as with other libraries you can do the following:
```c

#ifndef LIBRARY_TYPE_PREFIX
#define LIBRARY_TYPE_PREFIX library_
#endif

#define prefix(t) LIBRARY_TYPE_PREFIX ## t

typedef struct{int a; int b;} prefix(my_type);
```

However this will require a lot of typing in the header file (which will be typically slow).

- Ease of development

The library source code isn't required to use prefixes for it's names and it's types. So inside the library source code you can define prefix to be empty
```c
#define LIBRARY_TYPE_PREFIX
```
Thus when including header file, the source code of the library will get all the type names unprefixed, which makes the development of library a bit less painful and reduces typing in large libraries.

## Disatvantages

- Implies the usage of dynamic linking

Can not be a single-header library. Can impact startup performance a little.

- Possible portability issues

Not sure if that is true, but be aware. Some platforms may have different mechanisms of providing memory safety and module dynamic loading, so it might not work in some cases.

- Not backwards compatible

Loading a `.dll` that expects has different number or parameters of the functions from expected will result stack corruption.

- Can have performance impacts on function calls

I'm not sure whether calling a function from a struct has any performance impacts, I didn't check.

- Can be harder for introducing new functionality, compared to single header and other types of libraries.

Since you would have to
    1. Add new function definition.
    2. Load the pointer into the struct.
    3. Declare the function inside the struct.

Also the functions are cast to `void *` before being assigned. That could lead to potential bugs during the development related to not matching function signatures in the library and in the interface. (suggestion not to cast functions to `void *`)

## Possible improvements

- Prefix types using macro, have empty prefix in the library code and user defined prefix in the library.
