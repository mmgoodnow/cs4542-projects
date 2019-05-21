# Project 1
## Michael Goodnow, Zackary Mackay
We implimented two algorithims for this project, both standard greedy algorithims for the knapsack and graph coloring
problems respectively.The knapsack algorithim has a worst case runtime complexity of O(n)+ O(n log(n)) since the problem checks each item in the list once after the list is sorted by std::sort(). This algorithim will find a solution to the knapsack problem, but with our implimentation it is not garunteed to find the best case solution to every problem set since it chooses the items based on their cost to weight #ratios.

The graph coloring problem has a worse case runtime of O(n^2) since the algorithim will traverse the graph once and at each node it #will check every other node in the graph in the worst case. This algorithim can have varying results based on the graph it is given and the way the loops traverse the graph, as it may decide to add a color at the wrong time if the graph is not traversed correctly. 

