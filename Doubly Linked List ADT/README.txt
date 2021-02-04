noasulli
1687292

--------------------
       Lex.c
--------------------
This program uses the list ADT to sort the indices of an input file 
containing strings alphabetically, then writes the new sorted list of strings 
to an output file.

--------------------
       List.c
--------------------
A doubly linked list ADT, used to perform an insertion sort on the input
text file in Lex.c

--------------------
       List.h
--------------------
The header file for List.c, #include this file in any program you wish to use
the list library in.

--------------------
    ListClient.c
--------------------
A simple test harness for List.c, runs through a good portion of the functions,
can also use valgrind to check for memory leaks.

--------------------
      Makefile
--------------------
Used to compile and test the entire project.  Read the header for various
commands.