// Project 4: solving knapsack problem using a branch-and-bound solver
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

void expand_branch(const knapsack &branch, knapsack &best, subpq &subproblems) {

	if (!branch.isLegal()) {
		cout << "Illegal" << endl;
		return;
	}
	
	// set new best if branch as-is is better than current best
	if (branch.getValue() > best.getValue()) {
		best = branch;
		best.printSolution();
	}

	// don't bother expanding if the bound is worse than the current best
	if (branch.getBound() < best.getValue()) {
		cout << "Not good enough" << endl;
		return;
	}
	
	if (branch.getValue() == branch.getBound()) {
		cout << " Bound is equal to value " << endl;
		return;
	}
	
	if (branch.getNumDecided() >= branch.getNumObjects()) {
		cout << " Fully decided " << endl;
		return;
	}

	// branch
	knapsack b0(branch, branch.getNumDecided() + 1);
	knapsack b1(branch, branch.getNumDecided() + 1);

	// separate the branches
	b0.deselect(branch.getNumDecided());
	b1.select(branch.getNumDecided());

	// for each, add to the queue if it's promising
	if (b0.isLegal() && b0.getBound() > best.getValue()) {
		subproblems.push(b0);
	}
	if (b1.isLegal() && b1.getBound() > best.getValue()) {
		subproblems.push(b1);
	}
}

void branch_bound(knapsack &k, int secs) {
	subpq subproblems;

	knapsack currentSolution(k);
	greedy_knapsack(currentSolution);

	subproblems.push(k);

	while (!subproblems.empty()) {
		knapsack cur = subproblems.top();
		subproblems.pop();
		expand_branch(cur, currentSolution, subproblems);
		// cout << subproblems.size() << endl;
	}

	k = currentSolution;
}

int main(int argc, char *argv[]) {
	char x;
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

	branch_bound(k, 600);

	cout << endl << "Best solution" << endl;
	k.printSolution();

	return 0;
}
