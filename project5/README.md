# Project 5
## Michael Goodnow, Zackary Mackay

For this project I implemented a branch-and-bound solver for Project 4. It 
starts with a run-through of the greedy algorithm. Branches are stored in a 
priority queue, sorted by bound such that the algorithm expands branches with 
higher bounds first. I think that it may have been more efficient to not bother
with this and just use a normal stack or deque, because the algorithm fails to
improve on the greedy solution for the cases of 256, 512, and 1024 objects. I 
ran the 256 object instance overnight and it still didn't improve on the greedy 
solution at all. Originally it seemed like a good idea to expand the higher 
bounds first but now I'm not so sure it even gives a benefit and the heap 
operations, while O(log(n)), may just be unnecessary overhead. 
