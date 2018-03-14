

#include <cstdlib>

#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ostream>
#include <vector>
#include <bits/stdc++.h>
#define NUMTHREADS 8
using namespace std;


//Uriah Newkirk
//COM350 Program #2 (ATM)
//13 March 2018

vector<string> trans_v;	//vector holding list of transactions
//vector<pair<double,int> > tst;	//vector holding list of transactions
string inC, myS, finish;
double total_balance = 10000.00;
//stringstream code;

pthread_mutex_t mewtex1;
ofstream fout("activity.txt");

void *mods(void *tid) {

	int *local_id;
	double amount;
	local_id = (int *) tid;
	string process = trans_v[*local_id];
	int pos;
	for(int g=0;g<process.length();g++) {

		if(process.at(g)=='B') {

			pthread_mutex_lock(&mewtex1);
			fout << "Thread " << *local_id << " checks balance, balance is " << total_balance << endl;
			cout << "Thread " << *local_id << " checks balance, balance is  "  << total_balance << endl;
			pthread_mutex_unlock(&mewtex1);
		}
		
		else if(process.at(g)=='W') {
			if(process.find(' ',g)!=-1) {
			pos = process.find(' ',g);
			}
			else if(process.find('\n',g)!=-1) {
				pos = process.find('\n',g);
			}

			stringstream code(process.substr(g+1, pos-(g+1)));
			code >> amount;
			pthread_mutex_lock(&mewtex1);
			total_balance -= amount;
			//tst.push_back(make_pair(-amount, *local_id));
			//cout << "W TEST: " << process.substr(g+1, pos-(g+1)) << endl;
			fout << "Thread " << *local_id << " withdraws " << amount << ", balance is " << total_balance << endl;
			cout << "Thread " << *local_id << " withdraws " << amount << ", balance is " << total_balance << endl;
			pthread_mutex_unlock(&mewtex1);
		}
		else if(process.at(g)=='D') {
			if(process.find(' ',g)!=-1) {
			pos = process.find(' ',g);
			}
			else if(process.find('\n')!=-1) {
				pos = process.find('\n',g);
			}
			stringstream code(process.substr(g+1, pos-(g+1)));
			code >> amount;
			pthread_mutex_lock(&mewtex1);
			total_balance += amount;
			//tst.push_back(make_pair(amount, *local_id));	
			//cout << "D TEST: " << process.substr(g+1, pos-(g+1)) << endl;
			fout << "Thread " << *local_id << " deposits " << amount << ", balance is " << total_balance << endl;
			cout << "Thread " << *local_id << " deposits " << amount << ", balance is " << total_balance << endl;
			pthread_mutex_unlock(&mewtex1);		
		}
	}
}


int main(int argc, char * argv[]) {

	ifstream fin(argv[1]);
	trans_v.resize(NUMTHREADS);
	int pos, i = 0;
	while(getline(fin,inC,'\n')) {
		//get rid of spaces for B and D
			while(inC.find("D ")!=-1) {
			pos=inC.find("D ");
			//cout << "pos: " << pos << endl;
			inC.erase(pos+1,1);
                        //cout << inC << " after delete" << endl;
			}
			while(inC.find("W ")!=-1) {
			pos=inC.find("W ");
			//cout << "pos: " << pos << endl;
			inC.erase(pos+1,1);
			//cout << inC << " after delete" << endl;
                        }
                trans_v[i]=inC;
		//consider:
		//remove space between D/B & number
		//then store line into vector and read through
		//performing action based on first character
		//of the string
                i++;
	}

	cout << "input file:" << endl;
        for(int p=0;p<NUMTHREADS;p++) {
            cout << trans_v[p] << endl;
	}


	int h;
	int tids[NUMTHREADS];
	pthread_t threads[NUMTHREADS];
	pthread_attr_t attr;
	pthread_mutex_init(&mewtex1, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(h=0;h<NUMTHREADS;h++) {
		tids[h] = h;
		pthread_create(&threads[h], &attr, mods, (void *) &tids[h]);
	}
	for(h=0;h<NUMTHREADS;h++) {
		pthread_join(threads[h], NULL);
	}
	
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mewtex1);

	/*ofstream out ("test.txt");
	std::sort(tst.begin(), tst.end());
	out << tst.size() << endl;
	for (int i = 0; i < tst.size(); ++i) {
		out << tst[i].first << " " << tst[i].second << endl;	
	}*/
	cout << "The final balance is: " << total_balance << endl;
	fout << "The final balance is: " << total_balance << endl;
	//actual total: 11845
	pthread_exit(NULL);
	return 0;
}
