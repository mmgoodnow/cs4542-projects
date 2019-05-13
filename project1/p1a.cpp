// Project 1a: Solving knapsack using exhaustive search

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

bool shouldFlipBit(knapsack &k, int index) {
	for (int i = 0; i < index; i++) {
		if (!k.isSelected(i)) return false;
	}
	return true;
}

void incrementKnapsack(knapsack &k) {
	for (int bit = k.getNumObjects() - 1; bit >= 0; bit--) {
		if (shouldFlipBit(k, bit)) {
			if (k.isSelected(bit)) {
				k.unSelect(bit);
			} else {
				k.select(bit);
			}
		}
	}
}

void exhaustiveKnapsack(knapsack &k, int secs) {
	int bestValue = 0;

	knapsack currentBest;

	clock_t startTime = clock();

	while (true) {

		// check validity and compare value against current best
		if (k.getCost() <= k.getCostLimit() && k.getValue() > bestValue) {
			bestValue = k.getValue();
			currentBest = knapsack(k);
		}

		// terminate if we're on the last configuration
		if (shouldFlipBit(k, k.getNumObjects())) break;

		// terminate if it's been running too long
		if ((clock() - startTime) / CLOCKS_PER_SEC >= secs) break;

		incrementKnapsack(k);
	}

	k = knapsack(currentBest);
}

int main(int argc, char *argv[]) {
	char x;
	ifstream fin;
	if (argc != 2) {
		cout << "Usage:\n\t./p1a input_file" << endl;
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

		exhaustiveKnapsack(k, 600);

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
