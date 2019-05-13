#!/bin/bash
make
for if in knapsack/*.input; do
    of=${if/input/output}
    ./p1a $if > $of
for if in color/*.input; do
    of=${if/input/output}
    ./p1b $if > $of
done
make clean