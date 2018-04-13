
#include <cstdlib>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <semaphore.h>
using namespace std;
//Uriah Newkirk
//COMP350 Program #4 (Production Line)
// ## April 2018



//Questions
//what data type are the widgets?
//should I use stack.cpp?
pthread_mutex_t mewtex1, mewtex2, mewtex3;
ofstream fout("output3.txt");
sem_t oneQ, twoQ;
int one_t, two_t, three_t, queue_one=0, queue_two=0;


struct Widget {
	int id;
	int one;
	int two;
	int three;
};

vector<Widget> vecW;

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

/*
void *put(void *threadid) {

   long tid;
   tid = (long)threadid;
   pthread_mutex_lock(&mutex1);
   s.push(1);
   pthread_mutex_unlock(&mutex1);
   sem_post(&avail);
   printf("Leaving thread %d\n", tid);
   pthread_exit(NULL);
}

void *get(void *threadid) {
   long tid;
   tid = (long)threadid;
   sem_wait(&avail);
   pthread_mutex_lock(&mutex1);
   printf("Value consumed %d\n",s.pop());
   pthread_mutex_unlock(&mutex1);
   printf("Leaving thread %d\n", tid);
   pthread_exit(NULL);
}
*/

void *stage_one(void *oid) {

	int *local_id, k=0;
	local_id = (int *) oid;
	while(one_t<=100) {
		pthread_mutex_lock(&mewtex1);
		if(one_t>100) {
			pthread_mutex_unlock(&mewtex1);
			break;
		}
		vecW[one_t].one = *local_id;
		rough();
		cout << "Worker #" << vecW[one_t].one << " did rough() on Widget #" << vecW[one_t].id << endl;
		fout << "Worker #" << vecW[one_t].one << " did rough() on Widget #" << vecW[one_t].id << endl;
		sem_post(&oneQ);
		queue_one++;
		one_t++;
		pthread_mutex_unlock(&mewtex1);
	}
}


void *stage_two(void *tid) {

	int *local_id;
	local_id = (int *) tid;
	while(two_t<100) {
		pthread_mutex_lock(&mewtex2);
		if(two_t>=100) {
			pthread_mutex_unlock(&mewtex2);
			break;
		}
		if(queue_one>0) {
			queue_one--;
			sem_post(&oneQ);
		}
		else {
			pthread_mutex_unlock(&mewtex2);
			sem_wait(&oneQ);
			pthread_mutex_lock(&mewtex2);
		}
		vecW[two_t].two = *local_id;
		final_assembly();
		cout << "Worker #" << vecW[two_t].two << " did final assembly() on Widget #" << vecW[two_t].id << endl;
		fout << "Worker #" << vecW[two_t].two << " did final assembly() on Widget #" << vecW[two_t].id << endl;
		sem_post(&twoQ);
		queue_two++;
		two_t++;
		pthread_mutex_unlock(&mewtex2);
	}
}


void *stage_three(void *rid) {

	int *local_id;
	local_id = (int *) rid;
	while(three_t<100) {
		pthread_mutex_lock(&mewtex3);
		if(three_t>=100) {
			pthread_mutex_unlock(&mewtex3);
			break;
		}
		if(queue_two>0) {
			queue_two--;
			sem_post(&twoQ);
		}
		else {
			pthread_mutex_unlock(&mewtex3);
			sem_wait(&twoQ);
			pthread_mutex_lock(&mewtex3);
		}
		vecW[three_t].three = *local_id;
		paint();
		inspection();
		cout << "Worker #" << vecW[three_t].three << " did paint() and inspection() on Widget #" << vecW[three_t].id << endl;
		fout << "Worker #" << vecW[three_t].three << " did paint() and inspection() on Widget #" << vecW[three_t].id << endl;
		three_t++;
		pthread_mutex_unlock(&mewtex3);
	}
	

}


int main() {

	sem_init(&oneQ, 0, 0);
	sem_init(&twoQ, 0, 0);
	

	for(int x=0;x<100;x++) {
		vecW.push_back(Widget());
		vecW[x].id = x;
	}
	
	
	
	int h;
	int twoH=10, threeH=25;
	int oneid[10], twoid[15], threeid[5];
	pthread_t oneThreads[10];
	pthread_t twoThreads[15];
	pthread_t threeThreads[5];
	pthread_attr_t attr;
	pthread_mutex_init(&mewtex1, NULL);
	pthread_mutex_unlock(&mewtex1);
	pthread_mutex_init(&mewtex2, NULL);
	pthread_mutex_unlock(&mewtex2);
	pthread_mutex_init(&mewtex3, NULL);
	pthread_mutex_unlock(&mewtex3);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(h=0;h<10;h++) {
		oneid[h] = h;
		pthread_create(&oneThreads[h], &attr, stage_one, (void *) &oneid[h]);
	}
	for(h=0;h<15;h++) {
		twoid[h] = twoH;
		pthread_create(&twoThreads[h], &attr, stage_two, (void *) &twoid[h]);
		twoH++;
	}
	for(h=0;h<5;h++) {
		threeid[h] = threeH;
		pthread_create(&threeThreads[h], &attr, stage_three, (void *) &threeid[h]);
		threeH++;
	}
	for(h=0;h<10;h++) {
		pthread_join(oneThreads[h], NULL);
	}
	for(h=0;h<15;h++) {
		pthread_join(twoThreads[h], NULL);
	}
	for(h=0;h<5;h++) {
		pthread_join(threeThreads[h], NULL);
	}
	
	
	
	
	for(int c=0;c<100;c++) {
	
	}

	return 0;
}
