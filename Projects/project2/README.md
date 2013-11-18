# Project 2: Line Number

(10 points)

Write a program which copies stdin to stdout with the line numbers added. The numbers should be left-justified starting with column 1, and should be separated from the actual listing by a single tab. Test your program on the empty file, a file with one line, and a file with several lines. Demonstrate its correctness by comparing your output with the output of the UNIX's own wc utility.

Sample run:

    $ line_number < test.c

    1   #include <stdio.h>
    2   
    3   main() /* sample program */
    4   {
    5	printf("Hello world\n");
    6   }

    $ line_number < /dev/null
    
    $