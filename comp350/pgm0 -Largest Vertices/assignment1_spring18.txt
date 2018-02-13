Programming Assignment #1
Due 2-12-18 11:00 PM

Write a pthread program to determine the vertex or vetices with the 
maximum degree. Your program should use concurrency to sum each row of the given adjacency 
matrix, and then calculate the degree for each vertex. Find the vertex 
or vertices with the maximum. You should only use concurrency to find 
the degrees of each of the vertices. The rest should of the program 
should be done sequentially.
  

Input:

From the command line the user will provide file (named: graph.txt ). 
This file will be only the upper triangle of the adjacency matrix.

For example:

./a.out graph.txt

In this case, the numbers will be read into from the file input.txt. Note that this file may contain a total number of integers that is 
not a multiple of k.

Example contents of graph.txt
8
1 0 1 0 1 0 1
1 1 0 0 1 0
0 1 1 1 0
0 1 1 0
0 1 0 
0 1
1

Output:

Simply output on each line the degree of each vertex, and then output 
the vertex or vertices of maximum degree.

d(0) = 

Name your program 0.cpp and be sure to place it in your pgm directory.
