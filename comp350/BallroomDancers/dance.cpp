
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

//Uriah Newkirk
//COM350 Program #3 (Ballroom Dancers)
//20 April 2018

//mutex
//unlock = signal
//lock = wait

pthread_mutex_t mewtex1;
int fCount, lCount, f, l;
int the_followers=0, the_leaders=0;
sem_t followQ, leadQ, rendezvous;
ofstream fout;

void dance() {

	cout << "Leader " << l << " is dancing with Follower " << f << endl;
	fout << "Leader " << l << " is dancing with Follower " << f << endl;
}

void *leaders(void *lid) {
	
	int *local_id, k=0;
	//k is a local variable to help make sure everyone dances
	local_id = (int *) lid;

	while(k<fCount) {
		pthread_mutex_lock(&mewtex1);
		l=*local_id;
		if(the_followers > 0) {
			the_followers--;
			sem_post(&followQ);		//increment semaphore by 1
			//signal to the follower queue that a leader is now available
		}
		else {
			the_leaders++;
			pthread_mutex_unlock(&mewtex1);
			sem_wait(&leadQ);		//decrement semaphore by 1
			//wait in the queue until a follower is available
		}	
//		l = *local_id;
		dance();
		sem_wait(&rendezvous);
		pthread_mutex_unlock(&mewtex1);
		k++;
	}
//	cout << "Leader Thread " << *local_id << " done" << endl;
	pthread_exit(NULL);
}

void *followers(void *fid) {
	
	int *local_id, w=0;
	//w is a local variable to help make sure that everyone dances
	local_id = (int *) fid;
	
	while(w<lCount) {
		pthread_mutex_lock(&mewtex1);
		f=*local_id;
		if(the_leaders > 0) {
			the_leaders--;
			sem_post(&leadQ);		//increment semaphore by 1	
			//signal to the leader queue that a follower is available		
		}
		else {
			the_followers++;
			pthread_mutex_unlock(&mewtex1);
			sem_wait(&followQ);		//decrement semaphore by 1
			//wait in the queue until another leader is available
		}
//		f = *local_id;
		dance();
		sem_post(&rendezvous);
		w++;
	}
//	cout << "Follower Thread " << *local_id << " done" << endl;
	pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
	if(argc!=4) {
		cout << "Invalid input, sorry :) " << endl;
		return -1;
	}
	int n = atoi(argv[1]), m = atoi(argv[2]);
	fCount=m;
	lCount=n;
	fout.open(argv[3]);
	sem_init(&leadQ, 0, 0);
	sem_init(&followQ, 0, 0);
	sem_init(&rendezvous, 0, 0);

	
	int h;
	int lids[n];
	int fids[m];
	pthread_t lthreads[n];
	pthread_t fthreads[m];
	pthread_attr_t attr;
	pthread_mutex_init(&mewtex1, NULL);
	pthread_mutex_unlock(&mewtex1);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(h=0;h<n;h++) {
		lids[h] = h;
		pthread_create(&lthreads[h], &attr, leaders, (void *) &lids[h]);
	}
	for(h=0;h<m;h++) {
		fids[h] = h;
		pthread_create(&fthreads[h], &attr, followers, (void *) &fids[h]);
	}
	for(h=0;h<n;h++) {
		pthread_join(lthreads[h], NULL);
	}
	for(h=0;h<m;h++) {
		pthread_join(fthreads[h], NULL);
	}	
	sem_destroy(&followQ);
	sem_destroy(&leadQ);
	sem_destroy(&rendezvous);
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mewtex1);
return 0;
}
