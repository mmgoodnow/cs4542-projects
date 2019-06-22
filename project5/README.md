# Project 5
## Michael Goodnow, Zackary Mackay

For this project we implemented steepest descent and tabu search for knapsack and graph coloring. As with all local search algorithms, the main goal is to avoid local optima and keep searching for better solutions, which is the main improvement of the tabu search over the steepest descent search. 

We noticed that tabu search was a bit more consistent in its improvements with graph coloring over knapsack. We think that this is because of the difference between the two neighborhood functions we implemented. 

 - Knapsack: choose two items and toggle both their values. `O(n²)`
 - Graph coloring: choose one node and change its color. `O(nc)` where `n` is the number of nodes and `c` is the number of colors.

For the knapsack problem we chose this two-item neighborhood function because a simpler neighborhood function (toggle one item) would effectively result in a greedy algorithm based on value instead of value to weight ratio, which is worse than our greedy algorithm. So we expanded the size of the neighborhood by doing two items. This slows down the improvements quite a bit, especially in large instances, because of the large neighborhood, and may not be the best neighborhood function to use. However it was suitable enough for the task. 

The graph coloring neighborhood function seemed pretty logical, and its smaller cardinality resulted in a pretty efficient algorithm for tabu search. 

These algorithms are always useful as a final pass on whatever algorithm you already used, if it wasn't able to deliver you the optimal solution. And this was able to find the optimal solutions in 5 minutes, even for the largest graph coloring instances, where even CPLEX couldn't be sure of its solution in that time.

The two algorithms we tested made good use of their time. 

 - They performed more quickly and more optimally than the exhaustive algorithms. 
 - They were slower than the greedy algorithms but could perform more optimally ultimately, especially if used as post-processing on the greedy algorithms.
 - They were both outperformed by CPLEX in both speed and optimality, except for the largest few graph coloring cases. 
 - They outperformed the branch and bound algorithms in speed but given infinite time would have not guaranteed optimality which the BnB algorithms would.

