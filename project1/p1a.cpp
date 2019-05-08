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

void exhaustiveKnapsack(knapsack k, int secs) 
{
	int bestValue = 0;
	vector<bool> currentBest[k.getNumObjects()];

	clock_t startTime = clock();

	// http://www.programmingnotes.org/?p=4472
	for (unsigned i = 0; i < (unsigned) 1 << (k.getNumObjects()); i++) {
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
}

int main()
{
	char x;
	ifstream fin;
	stack <int> moves;
	string fileName;
	
	// Read the name of the file from the keyboard or
	// hard code it here for testing.
	
	// fileName = "knapsack16.input";

	cout << "Enter filename" << endl;
	cin >> fileName;
	
	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		cout << "Reading knapsack instance" << endl;
		knapsack k(fin);

		exhaustiveKnapsack(k, 600);

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



