/********************************************************
* File: sum.cpp
*   Example of a race condition associated with the
*   global variable total_sum. 
*
*   Output: total sum 
*
* Created: 1-29-18
*********************************************************/

#include <pthread.h>
#include <iostream>
using namespace std;

#define interval  100
#define numthreads  10
//((1000)*(1000))/2=500500

int total_sum = 0;

void *thread_sum(void *tid) {
  int i, sum = 0,*local_id, start, end;
  local_id = (int *) tid;
  start = (*local_id)*interval + 1;
  end = (*local_id+1)*interval + 1;
  for (i = start; i<end; i++ ) sum=sum+i;
  total_sum = total_sum + sum;
  return NULL;
}

int main(void) {
  int i;
  pthread_t threads[numthreads];
  int tids[numthreads];
  for(i = 0; i < numthreads; i++){
     tids[i] = i;
     if ( pthread_create( &threads[i], NULL, thread_sum, (void *) &tids[i]) ) {
     cout << "error creating thread."<<endl;
     return -1;
     }
  }

  for(i = 0; i < numthreads; i++){
  if ( pthread_join (threads[i], NULL ) ) {
     cout <<"error joining thread."<<endl;
     return -1;
     }
  }
  cout << "Our sum is " << total_sum << endl;
  return 0;

}
