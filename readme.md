## Description

This is an example of implementing a basic library performing simple algebra on 2 dimansional vectors, implemented using one of my ideas about library organisation and distribution. The library is structured in such a way as to compromize the uglyness of prefixed functions and significantly reduce the possibility of namespace collisions, as well as provide simple compatible interface between library and user code. 

The idea of the method is to do function "namespacing" by putting all the library declarations inside a struct defining the library interface. In order to use a library the library header defines a function that returns the pointer to that interface. It is possible that the library will have several such structs and therefore will have several initalization functions and several interfaces. The loader function is in the user's translation unit and is included together with the library header. The loader function loads the library's function that returns the pointer to the interface that library function also does version checking. The library interface is located in the library's translation unit.

The usage of the library will look like this:
```c
t_library_interface *library;

user_code() {
  if(0 == library_init(&library, "library.dll")) {
    printf("wrong version of the DLL or DLL is not found!\n");
    exit(1);
  }

  library->callFunction1();
  library->doSomething("cat");
}
```

The function names are scoped as struct fields on one side and by module on another side. So there is no function names leaking into the global scope of the user module. Additionally the struct to be filled with pointers is named by the user so it delegates the responsibility of managing name collisions to the user (and that managing is basically the same as managing variable names, so there is no overhead on the user side).

## Advantages
- Reduces possible name collisions for functions while reducing extra typing

A library can contain tens, hundreds and thousands of functions. It is possible that one of them collides with another function with another library. Since C language doesn't have namespaces, the library developers have started to namespace functions by appending `LIBRARY_` to the function names. This doesn't guarantee that the functions won't collide but it significantly reduces the possibility of the collision.

However with my approach there *Isn't even a possibility* that the functions will collide. Since the functions are struct members and the struct members don't collide.

Of couse this approach doesn't guarantee that library types, library defines and the loader function won't collide. 

- Ease of development

The library source code isn't required to use prefixes for it's names and it's types (since it is in another translation unit). This can significantly reduce typing.

- Private/Public procedures

Provides easy way to hide procedures that aren't supposed to be used by the user of the library (unlike single header libraries, that expose all procedures). That way the library can have however much procedures it wants to have and they can be named whatever you want, and you can arbitrarily choose which functions will make the API of the library.

- Simple versioning

The versioning can be done smartly by changing `MAJOR` and `MINOR` versions of the library. Those exists purely for the function of determining compatability. If new function is added to the library in a compatible way, `MINOR` is increased. This lets user use dll that has greater or equal amount of compatible functions that the user requires. However if the library introduces interface change, the `MAJOR` is increased. If majors don't match the library wouldn't be loaded. 

This is "simple" because if in one release the library introduces a new function (increasing `MINOR`), and in the next one updates the call to this function (updating `MAJOR`), the user could technically use the other functions in compatible mode. This library doesn't provide versioning system for each function separately, but it can theoretically be implemented, however it will complicate the library internals significantly.

## Disatvantages

- Implies the usage of dynamic linking

Can not be a single-header library. Can not be linked statically.

- Possible portability issues

Not sure if that is true, but be aware. Some platforms may have different mechanisms of providing memory safety and module dynamic loading, so it might not work in some cases.

Also the functions are cast to `void *` before being assigned. That could lead to potential bugs during the development related to not matching function signatures in the library and in the interface. (suggestion not to cast functions to `void *`)


## Possible improvements

- Prefix types using macro, have empty prefix in the library code and user defined prefix in the library.
- Store vtable of functions inside the dll, not in the user code. Return the pointer to the table to the user. That will get rid of stack overwrites and provide a ways of extending the API in backwards compatible way
- Versioning. Define library version, and if majors don't match in the DLL and the client, refuse to load the library and signal about it to the user.