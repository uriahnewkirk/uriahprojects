COMP 350
Spring 2018
Third Programming Assignment:

For this assignment, you will simulate a production line found in a 
typical Industrial plant. The manufacturing of these widgets requires 
three stages. The first stage requires 10 workers. In the first stage 
each worker does what is called the rough assemble of the widget. The 
second stage will do the final assembly. In this stage 15 workers are 
charged with this task. The third and final stage is where the widget 
gets painted and inspected. There are only 5 workers required for the
third and final stage. Your job is to simulate this manufacturing 
process using threads instead of workers. Each day the manufacturing
produces 100 widgets.

Each thread in stage 1 will call rough(). Each thread in stage 2 will 
call the final_assembly() method and in stage 3 each thread will call 
the methods paint() followed by inspection().

You must include these libraries:
#include <cstdlib>
#include <time.h>

void rough(){
     int i,n;
     srand((unsigned)time(NULL));
     n = int(1000*(1.0*rand()/RAND_MAX));
     for(i = 0; i<= n; i++);
}

void final_assembly(){
     int i,n;
     srand((unsigned)time(NULL));
     n = int(1000*(1.0*rand()/RAND_MAX));
     for(i = 0; i<= n; i++);
}

void paint(){
     int i,n;
     srand((unsigned)time(NULL));
     n = int(1000*(1.0*rand()/RAND_MAX));
     for(i = 0; i<= n; i++);
}

void inspection(){
     int i,n;
     srand((unsigned)time(NULL));
     n = int(1000*(1.0*rand()/RAND_MAX));
     for(i = 0; i<= n; i++);
}

Input: None

Output:

Write to a text file named output3.txt the following:

Example:
Worker thread 3 completes rough assembly on widget #

Worker thread 14 completes final assembly on widget #

Worker thread 1 completes rough assembly on widget #

Worker thread 22 completes painting and inspection on widget #
.
.
.

Name your program simulate.cpp and place it in your pgm directory.
