# Project 1
## Michael Goodnow, Zackary Mackay, Jie Fan

We implemented two algorithms for this project, an exhaustive algorithm for the knapsack problem and an exhaustive algorithm for graph coloring. 

The knapsack problem has a worst-case runtime complexity of O(2<sup>n</sup>) because each item is either in or out of the knapsack, and each new item therefore doubles the number of configurations. This exhaustive algorithm could be improved and still be exhaustive if we did some pre-processing on the list of items, such as sorting them by ratio of value to weight. As it is now, the problem is not even able to touch most of the items in the larger instances because it gets caught up with all the combinations of the first few items.

The graph coloring problem has a worst-case runtime complexity of O(ek<sup>n</sup>) because each node can be colored with k colors, and each new node therefore multiplies the number of configurations by k. For each iteration, the configuration has to be checked for its conflicts, which is dependent on the number of edges. 