# LIBEVOL

Collection of various libraries for personal use



| Library | Description                              | Depends                            |
| ------- | ---------------------------------------- | ---------------------------------- |
| except  | exception handler                        | _stdio_, _setjmp_                  |
| strace  | function call stack tracer               | _stdlib_, _stdio_                  |
| garbage | garbage manager (not collector)          | _stdlib_                           |
| fpow10  | fast 10 powers (used by string library)  |                                    |
| string  | string library for garbage managed string manipulation | _stdio_, _stdarg_, garbage, fpow10 |
| vector  | garbage managed dynamic array library    | strace, except, garbage            |

