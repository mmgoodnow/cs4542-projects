param n;
param costBound;
param value{i in 0..n-1};
param cost{i in 0..n-1};

var x {i in 0..n-1} binary;

maximize objective: sum {i in 0..n-1} value[i] * x[i];
subject to c1: 
sum {i in 0..n-1} cost[i] * x[i] <= costBound;