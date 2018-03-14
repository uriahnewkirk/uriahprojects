/***************************************************************************
* File: file_sharing.cpp
* Description: This program demostrates cooridination
* between threads through the use of binary semaphores  (mutex).
*
* Last revised 2-4-05
*****************************************************************************/

#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;



pthread_mutex_t mutex1;
pthread_mutex_t mutex2;


void *output(void *tid) 
{
	
	sleep(1);
	pthread_mutex_lock(&mutex1);
	cout << "locking resource 1 (output)" << endl;
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex2);
	cout << "locking resource 2 (output)" << endl;
	pthread_mutex_unlock(&mutex2);
	cout << "leaving output" << endl;
	pthread_exit(NULL);
}

void *out(void *tid) 
{	
	sleep(1);
	pthread_mutex_lock(&mutex1);
	cout << "locking resource 1 (out)" << endl;
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex2);
	cout << "locking resource 2 (out)" << endl;	
	pthread_mutex_unlock(&mutex2);
	cout << "leaving out" << endl;
	pthread_exit(NULL);
}

int main(){
	int thread_id = 1;
	pthread_t threads[2];
	pthread_attr_t attr;
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	// create two threads
	pthread_create(&threads[0], &attr, output, (void *) &thread_id);
	thread_id ++;
	pthread_create(&threads[1], &attr, out, (void *) &thread_id);
	// Wait until threads complete writing
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	// Clean up and exit
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
	pthread_exit(NULL);
	return 0;
}

	
