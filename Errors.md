# Common GCC Errors #

## Linker ##

- `undefined reference to <class member>` The member is in your header file but you forgot to define it in your cpp file
- `undefined reference to vtable for <class>` There are virtual methods in that class or one of its superclasses that aren't pure (` = 0`) and aren't implemented. Add a body or make them pure.

## Compiler ##

- `<xyz> does not name a type` You forgot to `#include "xyz.h"`