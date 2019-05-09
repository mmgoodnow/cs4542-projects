// Project 1a: Solving knapsack using exhaustive search
//

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <time.h>
#include <cmath>

using namespace std;

#include "d_except.h"
#include "d_matrix.h"
#include "knapsack.h"

bool shouldFlipBit(vector<bool> bits, int index) {
	for (int i = index - 1; i >= 0; i--) {
		if (bits[i] == 0) return false;
	}
	return true;
}

knapsack exhaustiveKnapsack(knapsack k, int secs) 
{
	int bestValue = 0;
	vector<bool> currentBest (k.getNumObjects(), false);

	clock_t startTime = clock();

	// http://www.programmingnotes.org/?p=4472
	while (true) {
		cout << i << endl;
		for (int bit = 0; bit < k.getNumObjects(); bit++) {
			if ((i >> bit) & 1) {
				k.select(bit);
			} else {
				k.unSelect(bit);
			}
		}
		if (k.getCost() <= k.getCostLimit() && k.getValue() > bestValue) {
			bestValue = k.getValue();
			for (int j = 0; j < k.getNumObjects(); j++) {
				currentBest[j] = k.isSelected(j);
			}
		}

		if ((clock() - startTime) / CLOCKS_PER_SEC >= secs) break;
	}

	for (int j = 0; j < k.getNumObjects(); j++) {
		if (currentBest[j]) {
			k.select(j);
		} else {
			k.unSelect(j);
		}
	}

	return k;
}

int main(int argc, char** argv)
{
	char x;
	ifstream fin;
	if (argc != 2) {
		cout << "Usage:\n\t./p1a input_file" << endl;
	}
	fin.open(argv[1]);
	if (!fin)
	{
		cerr << "Cannot open " << argv[1] << endl;
		exit(1);
	}

	try
	{
		cout << "Reading knapsack instance" << endl;
		knapsack k(fin);

		k = exhaustiveKnapsack(k, 600);

		cout << endl << "Best solution" << endl;
		k.printSolution();
		
	}    

	catch (indexRangeError &ex) 
	{ 
		cout << ex.what() << endl; exit(1);
	}
	catch (rangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
}



