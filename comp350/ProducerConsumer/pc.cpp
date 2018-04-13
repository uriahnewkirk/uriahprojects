/******************************************************************************
* FILE: pc.cpp
*
* DESCRIPTION: Simulation of producer/consumer using semaphores and mutex
*
* global variables: mutex1 controls who gets access to the stack, avail a semaphore to
* make sure the queue has something on it to consume
* 

* 
* AUTHOR: Ed Carr
*
******************************************************************************/

#include <pthread.h>
#include <cstdlib>
#include <cstdio>
#include <semaphore.h>
#include "stack.cpp"

#define NUM_THREADS	50

// Assuming only three stages
sem_t  avail;
pthread_mutex_t mutex1;
stack <int> s(100);


// Function used by each producer to place id on stack

void *put(void *threadid)
{
   long tid;
   tid = (long)threadid;
   pthread_mutex_lock(&mutex1);
   s.push(1);
   pthread_mutex_unlock(&mutex1);
   sem_post(&avail);
   printf("Leaving thread %d\n", tid);
   pthread_exit(NULL);
}

void *get(void *threadid)
{
   long tid;
   tid = (long)threadid;
   sem_wait(&avail);
   pthread_mutex_lock(&mutex1);
   printf("Value consumed %d\n",s.pop());
   pthread_mutex_unlock(&mutex1);
   printf("Leaving thread %d\n", tid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t producers[NUM_THREADS/2];
   pthread_t consumers[NUM_THREADS/2];
   int rc;
   long t,x;
   sem_init(&avail, 0, 0);
   // Producers/Consumers created
   for(t=0;t<NUM_THREADS/2;t++){
     rc = pthread_create(&producers[t], NULL, put, (void *)t);
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
     x = t + NUM_THREADS/2;
     rc = pthread_create(&consumers[t], NULL, get, (void *)x);
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
     }

   for( t = 0; t < NUM_THREADS/2; t++){
      pthread_join(producers[t], 0);
      pthread_join(consumers[t], 0);
   }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
