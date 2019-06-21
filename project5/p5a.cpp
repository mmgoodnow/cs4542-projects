// Project 5a: solving knapsack problem using local search
// Michael Goodnow

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <list>
#include <queue>
#include <time.h>
#include <vector>

using namespace std;

#include "knapsack.h"

typedef priority_queue<knapsack, vector<knapsack>, compare_bound> subpq;

// Solve the knapsack problem using a greedy algorithm.
void greedy_knapsack(knapsack &k) {

	vector<pair<int, float>> vec;
	for (int i = 0; i < k.getNumObjects(); i++) {
		pair<int, float> p(i, k.valueCostRatio(i));
		vec.push_back(p);
	}
	sort(vec.begin(), vec.end(), compare_knapsack_objects());

	int currentCost = 0;
	for (int i = 0; i < vec.size(); ++i) {
		int obj = vec[i].first;
		if (k.getCost(obj) + currentCost <= k.getCostLimit()) {
			k.select(obj);
			currentCost += k.getCost(obj);
		}
	}
}
//Solve the knapsack problem using local search
void steepest_descent(knapsack &k, int secs) {
	clock_t startTime = clock();
	while(1){
		knapsack candidate = k.bestNeighbor();
		if(k.getValue() < candidate.getValue()){
			k = candidate;
			// terminate if it's been running too long
			if ((clock() - startTime) / CLOCKS_PER_SEC >= secs) break;
		}
		else {
			break;
		}

	
		


int main(int argc, char *argv[]) {
	char x;
	int secs = 0;
	ifstream fin;
	if (argc != 2) {
		cerr << "Usage:\n\t./p4 input_file" << endl;
		exit(1);
	}
	fin.open(argv[1]);
	if (!fin) {
		cerr << "Cannot open " << argv[1] << endl;
		exit(1);
	}

	knapsack k(fin);
	cout << "Done reading knapsack instance" << endl;
	cout << "Please input time constraint:"<<endl;
	cin >>secs>>endl;
	
	steepest_descent(k,secs);
	
	cout << endl << "Best solution" << endl;
	k.printSolution();

	return 0;
}
