// Code to read graph instances from a file.	 Uses the Boost Graph Library
// (BGL).

#include "d_except.h"
#include <fstream>
#include <iostream>
#include <limits.h>
#include <vector>

#include <boost/graph/adjacency_list.hpp>

#define LargeValue 99999999

using namespace std;
using namespace boost;

int const NONE = -1; // Used to represent a node that does not exist

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties,
                       EdgeProperties>
    Graph;

struct VertexProperties {
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred;
	bool visited;
	bool marked;
	int weight;
};

// Create a struct to hold properties for each edge
struct EdgeProperties {
	int weight;
	bool visited;
	bool marked;
};

// Initialize g using data from fin.
void initializeGraph(Graph &g, ifstream &fin) {
	int n, e;
	int j, k;

	fin >> n >> e;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
		v = add_vertex(g);

	for (int i = 0; i < e; i++) {
		fin >> j >> k;
		add_edge(j, k, g); // Assumes vertex list is type vecS
	}
}

bool shouldIncrementAtIndex(const vector<int> &config, int numColors,
                            int index) {
	for (int i = 0; i < index; i++) {
		if (config[i] != numColors - 1) return false;
	}
	return true;
}

void incrementConfig(vector<int> &config, int numColors) {
	for (int digit = config.size() - 1; digit >= 0; digit--) {
		if (shouldIncrementAtIndex(config, numColors, digit)) {
			config[digit]++;
			config[digit] %= numColors;
		}
	}
}

void printConfig(vector<int> &config) {
	for (int i = 0; i < config.size(); i++) {
		cout << config[i] << " ";
	}
	cout << endl;
}

int numConflicts(Graph &g)

int exhaustiveColoring(Graph &g, int numColors, int t) {
	int lowestConflicts = LargeValue
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
		if (shouldIncrementAtIndex(config, numColors, config.size())) break;

		// terminate if it's been running too long
		if ((clock() - startTime) / CLOCKS_PER_SEC >= secs) break;
	}
}

// Set all node weights to w.
void setNodeWeights(Graph &g, int w) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange =
	    vertices(g);

	for (Graph::vertex_iterator vItr = vItrRange.first;
	     vItr != vItrRange.second; ++vItr) {
		g[*vItr].weight = w;
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
		cout << "Reading graph" << endl;
		Graph g;
		initializeGraph(g, fin);

		cout << "Num nodes: " << num_vertices(g) << endl;
		cout << "Num edges: " << num_edges(g) << endl;
		cout << endl;

		// cout << g;
	}
	return 0;
}
