/*
Assignment:
Write a pthread program to determine the vertex or vetices with the
maximum degree. Your program should use concurrency to sum each row of the given adjacency 
matrix, and then calculate the degree for each vertex. Find the vertex
or vertices with the maximum. You should only use concurrency to find
the degrees of each of the vertices. The rest should of the program 
should be done sequentially.
 */

#include <cstdlib>

#include <pthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Uriah Newkirk
//12 February 2018
//COMP350 pgm0

int vertex, p2=0, inV, total_sum, hSum=0;
vector<vector<int> > the_v;	//2d vector holding graph
vector<int> sumV;		//vector holding degree sums


void *thread_sum(void *tid) {
   int i, sum=0, *local_id;
   local_id = (int *) tid;

   for(int j=0;j<vertex;j++) {
      sum = sum + the_v[*local_id][j];
      //cout << "value: " << the_v[*local_id][j] << endl;
      //each thread will sum the degree of its vertex
      }
   sumV[*local_id] = sum;
   total_sum = total_sum + sum;
   //not really necessary since we only care which has the highest degree

   return NULL;
}


int main(int argc, char * argv[]) {
   int h;
   fstream fin(argv[1]); //"./a.out filename.cpp"
   fin >> vertex;	 //read first value in file as vertex
   the_v.resize(vertex); //resize vector to fit newly discovered vertex value

   for(int y=0;y<vertex;y++) {
      the_v[y].resize(vertex);
      //resize each inner vector in the 2d vector
      }
      sumV.resize(vertex);
      //only 1 resize required for single dimension vector
   for(int w=0;w<=vertex;w++) {
      p2=w+1;
      //only consider the right half of matrix that is given in txt file 
      for(p2;p2<vertex;p2++) {
            fin >> inV;	//read in 1 or 0 into the int variable
            the_v[w][p2] = inV;
            the_v[p2][w] = inV;
            //add the edge to the graph, as well as it's recipricol ((4,2) as well as (2,4))
            }
         }


         for(int u=0;u<vertex;u++) {
            for(int b=0;b<=vertex;b++) {
               cout << the_v[u][b] << " ";
               }
            cout << " " << endl;
         }
	 //Print out the graph to make sure everything went okay
	 //be sure to use "<=" on second for loop to include the extra row
	 //(or not because it'll always be 0 before any calculations are done)



         pthread_t threads[vertex];
         int tids[vertex];
         for(h=0;h<vertex;h++) {
            tids[h] = h;
            if(pthread_create( &threads[h], NULL, thread_sum, (void *) &tids[h]) ) {
            cout << "error creating thread." << endl;
            return -1;
            }
         }
         for(h=0;h<vertex;h++) {
            if(pthread_join (threads[h], NULL)) {
               cout << "error joining thread" << endl;
               return -1;
               }
            }
            //pthread code given by instructor




            for(int o=0;o<vertex;o++) {
               cout << "d(" << o << ") = " << sumV[o] << endl;
               if(sumV[o] > hSum)
                  hSum = sumV[o];
               }
               //Print out the degree of each vertex


               cout << "highest degree vertices: " << endl;
               for(int f=0;f<vertex;f++) {
                  if(sumV[f]==hSum)
                     cout << f << endl;
                  }
                  //Print out all vertices with the highest degree

                  return 0;

         }
