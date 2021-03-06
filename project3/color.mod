# ILP model for graph coloring

# number of nodes
param numNodes;

# number of Colors
param numColors;

set edgeList dimen 2;

# edge[op1,op2] = 1 iff (i,j) is in edgeList
param edge {i in 0..numNodes-1, j in 0..numNodes-1} := 
(if (i,j) in edgeList or (j,i) in edgeList then 1 else 0);

# color[i,c] = true means that node i is assigned color c
var color {i in 0..numNodes-1, c in 0..numColors-1} binary;

# conflict[i,j] = true means that there is a conflict in the
# coloring of nodes i and j.

var conflict {i in 0..numNodes-1, j in 0..numNodes-1} binary;

# Objective function
minimize total_conflicts: 
	sum {i in 0..numNodes-1, j in 0..numNodes-1} conflict[i, j] / 2;

# Each node should have exactly one color
subject to color_constraint {n in 0..numNodes-1}:
	sum {c in 0..numColors-1} color[n,c] = 1;

# Make sure conflicts are detected
subject to detect_conflicts {
	i in 0..numNodes-1, 
	j in 0..numNodes-1, 
	c in 0..numColors-1
}: 
	# RHS will be 
	#	0 (no edge or no selected colors), 
	#	1 (edge exists but colors don't conflict), or 
	#	2 (conflict), 
	# so conflict[i, j] must be 1 if there's a conflict
	conflict[i, j] + edge[i, j] >= edge[i, j] * (color[i, c] + color[j, c])
