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

bool shouldFlipBit(vector<bool> bits, int index) {
	for (int i = 0; i < index; i++) {
		if (bits[i] == 0) return false;
	}
	return true;
}

void exhaustiveKnapsack(knapsack &k, int secs) {
	int bestValue = 0;
	vector<bool> currentBest(k.getNumObjects(), false);
	vector<bool> currentConfig(k.getNumObjects(), false);

	clock_t startTime = clock();

	while (true) {

		// check validity and compare value against current best
		if (k.getCost() <= k.getCostLimit() && k.getValue() > bestValue) {
			bestValue = k.getValue();
			for (int j = 0; j < k.getNumObjects(); j++) {
				currentBest[j] = k.isSelected(j);
			}
		}

		// iterate currentConfig by walking down the bits backwards to
		// determine if they should be flipped
		for (int bit = k.getNumObjects() - 1; bit >= 0; bit--) {
			if (shouldFlipBit(currentConfig, bit)) {
				currentConfig[bit] = !currentConfig[bit];
			}
		}

		// set k to currentConfig
		for (int bit = 0; bit < k.getNumObjects(); bit++) {
			if (currentConfig[bit]) {
				k.select(bit);
			} else {
				k.unSelect(bit);
			}
		}

		// terminate if we're on the last configuration
		if (shouldFlipBit(currentConfig, k.getNumObjects())) break;

		// terminate if it's been running too long
		if ((clock() - startTime) / CLOCKS_PER_SEC >= secs) break;
	}

	// set subset back to current best
	for (int j = 0; j < k.getNumObjects(); j++) {
		if (currentBest[j]) {
			k.select(j);
		} else {
			k.unSelect(j);
		}
	}
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
