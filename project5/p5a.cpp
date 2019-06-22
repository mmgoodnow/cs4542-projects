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
// Solve the knapsack problem using steepest decent
void steepest_descent(knapsack &k, int secs) {
	clock_t startTime = clock();
	while (1) {
		knapsack candidate = k.bestNeighbor();
		if (k.getValue() < candidate.getValue()) {
			k = candidate;
			// terminate if it's been running too long
			if ((clock() - startTime) / CLOCKS_PER_SEC >= secs) break;
		} else {
			break;
		}
	}
}
void tabu_search(knapsack &k, int secs) {
	clock_t startTime = clock();
	deque<knapsack> tabul;
	knapsack champion(k);
	while (true) {
		
		// find a candidate not on the list
		knapsack candidate = k.bestNeighborTabu(tabul);
		
		// add to tabu list
		tabul.push_front(candidate);
		
		// remove the oldest item on the list if the list is size > 10
		if (tabul.size() > 10) {
			tabul.pop_back();
		}
		
		// assign new best neighbor
		k = candidate;
		
		if (k.getValue() > champion.getValue()) {
			// assign new champion
			champion = k;
		}
		
		// terminate if it's been running too long
		if ((clock() - startTime) / CLOCKS_PER_SEC >= secs) break;
	}
	k = champion;
}

int main(int argc, char *argv[]) {
	char x;
	ifstream fin;
	if (argc != 3) {
		cerr << "Usage:\n\t./p5b {steep, tabu} input_file" << endl;
		exit(1);
	}
	fin.open(argv[2]);
	if (!fin) {
		cerr << "Cannot open " << argv[1] << endl;
		exit(1);
	}
	
	cerr << argv[0] << " " << argv[1] << " " << argv[2] << endl;

	knapsack k(fin);
	cerr << "Done reading knapsack instance" << endl;
	
	if (!strcmp(argv[1], "steep")) {
		steepest_descent(k, 300);
	} else if (!strcmp(argv[1], "tabu")) {
		tabu_search(k, 300);
	} else if (!strcmp(argv[1], "greedy,steep")) {
		greedy_knapsack(k);
		steepest_descent(k, 300);
	} else if (!strcmp(argv[1], "greedy,tabu")) {
		greedy_knapsack(k);
		tabu_search(k, 300);
	} else {
		cerr << "Usage:\n\t./p5b {steep, tabu} input_file" << endl;
		exit(1);
	}

	cout << endl << "Best solution" << endl;
	k.printSolution();

	return 0;
}
