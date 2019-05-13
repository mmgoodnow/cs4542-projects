// Project 1b: Solving graph coloring using exhaustive search
// Michael Goodnow, Zackary Mackay, Jie Fan

#include "d_except.h"
#include <climits>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties,
                       EdgeProperties>
    Graph;

// convenience types
typedef Graph::vertex_iterator v_itr;
typedef Graph::edge_iterator e_itr;
typedef Graph::edge_descriptor e_dsc;
typedef Graph::vertex_descriptor v_dsc;

// only using color
struct VertexProperties {
	int color;
};

// no edge properties
struct EdgeProperties {};

// Initialize g using data from fin.
void initializeGraph(Graph &g, ifstream &fin) {
	int n, e;
	int j, k;

	fin >> n >> e;
	v_dsc v;

	// Add nodes.
	for (int i = 0; i < n; i++) {
		v = add_vertex(g);
	}

	for (int i = 0; i < e; i++) {
		fin >> j >> k;
		add_edge(j, k, g); // Assumes vertex list is type vecS
	}
}

// Determine whether the color at index should be incremented based on the
// lesser significance digits
bool shouldIncrementAtIndex(Graph &g, int numColors, int index) {
	pair<v_itr, v_itr> r = vertices(g);

	// make sure that the index is within range
	assert(r.first + index <= r.second);

	for (v_itr i = r.first; i < (r.first + index); ++i) {
		if (g[*i].color != numColors - 1) return false;
	}
	return true;
}

// Increment the coloring configuration for this graph
void incrementColoring(Graph &g, int numColors) {
	pair<v_itr, v_itr> r = vertices(g);
	for (v_itr i = r.second - 1; i >= r.first; --i) {
		if (shouldIncrementAtIndex(g, numColors, i - r.first)) {
			g[*i].color++;
			g[*i].color %= numColors;
		}
	}
}

// Determine the number of coloring conflicts in the graph
int numConflicts(Graph &g) {
	int conflicts = 0;
	pair<e_itr, e_itr> r = edges(g);
	// Loop over all edges in the graph
	for (e_itr i = r.first; i != r.second; ++i) {

		// conflicts are when neighboring nodes have the same color
		e_dsc ed = *i;
		v_dsc tgt = target(ed, g);
		v_dsc src = source(ed, g);
		if (g[tgt].color == g[src].color) conflicts++;
	}
	return conflicts;
}

// Exhaustively examine all the coloring options for the graph, until it's
// been running for secs seconds.
int exhaustiveColoring(Graph &g, int numColors, int secs) {
	int lowestConflicts = INT_MAX;
	Graph lowestConflictsGraph;
	clock_t startTime = clock();
	while (true) {

		// compare value against current best
		int conflicts = numConflicts(g);
		if (numConflicts(g) < lowestConflicts) {
			lowestConflicts = conflicts;
			cerr << lowestConflicts << endl;
			lowestConflictsGraph = g;
			assert(numConflicts(lowestConflictsGraph) == numConflicts(g));
		} else {
			assert(numConflicts(lowestConflictsGraph) <= numConflicts(g));
		}

		// terminate if we're on the last configuration
		if (shouldIncrementAtIndex(g, numColors, num_vertices(g))) break;

		// terminate if it's been running too long
		if ((clock() - startTime) / CLOCKS_PER_SEC >= secs) break;

		incrementColoring(g, numColors);
	}
	g = lowestConflictsGraph;
	return lowestConflicts;
}

// print the number of conflicts and the coloring configuration
void printSolution(Graph &g) {
	cout << "------------------------------------------------" << endl;
	cout << "Num conflicts: " << numConflicts(g) << endl;
	pair<v_itr, v_itr> r = vertices(g);

	for (v_itr i = r.first; i < r.second; ++i) {
		cout << *i << " " << g[*i].color << endl;
	}
}

int main(int argc, char *argv[]) {
	ifstream fin;
	if (argc != 2) {
		cerr << "Usage:\n\t./p1a input_file" << endl;
		exit(1);
	}
	fin.open(argv[1]);
	if (!fin) {
		cerr << "Cannot open " << argv[1] << endl;
		exit(1);
	}

	try {
		cerr << "Reading graph" << endl;
		Graph g;
		int numColors;
		fin >> numColors;
		initializeGraph(g, fin);

		cout << "Num colors: " << numColors << endl;
		cout << "Num nodes: " << num_vertices(g) << endl;
		cout << "Num edges: " << num_edges(g) << endl;
		cout << endl;

		exhaustiveColoring(g, numColors, 600);

		printSolution(g);

	} catch (indexRangeError &ex) {
		cerr << ex.what() << endl;
		exit(1);
	} catch (rangeError &ex) {
		cerr << ex.what() << endl;
		exit(1);
	}
	return 0;
}
