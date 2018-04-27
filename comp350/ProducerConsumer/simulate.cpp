
#include <cstdlib>
#include <queue>
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
int one_t=1, two_t, three_t, wC=1;
int wC2=1, wC3=1;


struct Widget {
	int id;
	int one;
	int two;
	int three;
};

queue<Widget> widQ1, widQ2;;

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
	
	int *local_id, k=1;
	Widget w;
	local_id = (int *) oid;
	while(wC<=100)  {
		rough();
		pthread_mutex_lock(&mewtex1);
		if(wC<=100) {
			w.one = *local_id;
			w.id = wC;
			cout << "Worker thread " << w.one << " did rough() on Widget #" << w.id  << endl;
			fout << "Worker thread " << w.one << " did rough() on Widget #" << w.id << endl;
			widQ1.push(w);
			wC++;
		}
		pthread_mutex_unlock(&mewtex1);
		sem_post(&oneQ);
	}

	pthread_exit(NULL);
}


void *stage_two(void *tid) {
	
	int *local_id;
	Widget w;
	local_id = (int *) tid;
	sem_wait(&oneQ);
	while(wC2<=100) {
		final_assembly();
		pthread_mutex_lock(&mewtex2);
		if(wC2<=100 && widQ1.size()>0) {
//			pthread_mutex_lock(&mewtex2);
			w = widQ1.front();
			widQ1.pop();
			w.two = *local_id;
			cout << "Worker thread " << w.two << " did final assembly() on Widget #" << w.id <<  endl;
			fout << "Worker thread " << w.two << " did final assembly() on Widget #" << w.id << endl;
			wC2++;
		}
//		pthread_mutex_unlock(&mewtex2);
		if(widQ2.size()<100) {
//			pthread_mutex_lock(&mewtex2);
			widQ2.push(w);
//			pthread_mutex_unlock(&mewtex2);
		}
		pthread_mutex_unlock(&mewtex2);
		sem_post(&twoQ);
	}
	pthread_exit(NULL);
}


void *stage_three(void *rid) {
	
	int *local_id;
	Widget w;
	local_id = (int *) rid;
	sem_wait(&twoQ);
	while(wC3<=100) {
		paint();
		inspection();
		pthread_mutex_lock(&mewtex3);
		if(wC3<=100 && widQ2.size()>0) {
			w = widQ2.front();
			widQ2.pop();
			w.three = *local_id;
			if(w.id!=wC3) {
				w.id=wC3;
			}
			cout << "Worker thread " <<w.three << " did paint() and inspection() on Widget #" << w.id << endl;
			fout << "Worker thread " <<w.three << " did paint() and inspection() on Widget #" << w.id << endl;
			wC3++;
		}
		pthread_mutex_unlock(&mewtex3);
	}
	pthread_exit(NULL);
}


int main() {

	sem_init(&oneQ, 0, 0);
	sem_init(&twoQ, 0, 0);
	
	
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
	return 0;
}
