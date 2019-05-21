// Project 2a: Solving knapsack using a greedy algorithm
// Michael Goodnow, Zackary Mackay

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <list>
#include <queue>
#include <time.h>
#include <vector>

using namespace std;

#include "d_except.h"
#include "d_matrix.h"
#include "knapsack.h"

// Sort comparator that will take a pair of knapsack object id and float which
// is the ratio of value to weight
struct compare_knapsack_objects {
	bool operator()(pair<int, float> &a, pair<int, float> &b) {
		return a.second > b.second;
	}
};

// Solve the knapsack problem using a greedy algorithm.
void greedyKnapsack(knapsack &k) {

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

int main(int argc, char *argv[]) {
	char x;
	ifstream fin;
	if (argc != 2) {
		cerr << "Usage:\n\t./p2a input_file" << endl;
		exit(1);
	}
	fin.open(argv[1]);
	if (!fin) {
		cerr << "Cannot open " << argv[1] << endl;
		exit(1);
	}

	try {
		cout << "Reading knapsack instance" << endl;
		knapsack k(fin);

		greedyKnapsack(k);

		cout << endl << "Best solution" << endl;
		k.printSolution();

	}

	catch (indexRangeError &ex) {
		cout << ex.what() << endl;
		exit(1);
	} catch (rangeError &ex) {
		cout << ex.what() << endl;
		exit(1);
	}
	return 0;
}
