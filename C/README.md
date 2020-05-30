Our program will read in a file depicting an initial configuration for the world. By default, the file's name will be "input.txt". A different file name may be specified by the user on the command line. <br/>
The program will generate and display a "world" based on the input file. The actual number of rows and columns in the world may be different than what is in the file. Default values for both the number of rows and the number of columns will be 10. Again, different values can be provided on the command line.<br/>
If there are fewer lines in the file or some lines are shorter than expected, the missing "cells" will be assumed to be dead.<br/>
If there are more lines in the file or some lines are longer than expected, then ignore the extra cells.<br/>
After displaying the initial state, the program will proceed to calculate some number of additional generations, displaying each in turn. The number of generations will be 10 by default, but a different value may be provided on the command line.

The program is run from the command line as follows:
```
$ make
$ ./life rows columns filename generations
```

Language Features:
```
C is a general-purpose, high-level language that was originally developed by Dennis M. Ritchie to develop the UNIX operating system.
The two main advantages of this language are efficiency and it can handle low-level activities such as easy manipulation of pointers.

Unlike the stack where memory is allocated and released in a very defined order, heap is a location in memory where memory may be allocated at random access.
The heap is not managed automatically for you, and is not as tightly managed by the CPU. You must use malloc() or calloc() to allocate memory on the heap and free() to deallocate. If you fail to deallocate, your program will have what is known as a memory leak.

Stack
- very fast access
- don't have to explicitly de-allocate variables
- space is managed efficiently by CPU, memory will not become fragmented
- local variables only
- limit on stack size (OS-dependent)
- variables cannot be resized
Heap
- variables can be accessed globally
- no limit on memory size
- (relatively) slower access
- no guaranteed efficient use of space, memory may become fragmented over time as blocks of memory are allocated, then freed
- you must manage memory (you're in charge of allocating and freeing variables)
- variables can be resized using realloc()
```