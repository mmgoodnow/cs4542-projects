#!/bin/bash
make
N=4
(
for if in knapsack/*.input; do
	((i=i%N)); ((i++==0)) && wait
    of=${if/input/output}
    echo "./p1a $if > $of"
    ./p1a $if > $of &
done
for if in color/*.input; do
	((i=i%N)); ((i++==0)) && wait
    of=${if/input/output}
    echo "./p1b $if > $of"
    ./p1b $if > $of &
done
)
wait
make clean