#!/bin/bash
# https://unix.stackexchange.com/questions/103920
open_sem(){
    mkfifo pipe-$$
    exec 3<>pipe-$$
    rm pipe-$$
    local i=$1
    for((;i>0;i--)); do
        printf %s 000 >&3
    done
}

run_with_lock(){
    local x
    read -u 3 -n 3 x && ((0==x)) || exit $x
	(
	 ( "$@"; )
	printf '%.3d' $? >&3
	)&
}

make
N=4
open_sem $N
for if in knapsack/*.input; do
	of=${if/input/output}
	echo "./p1a $if > $of"
	run_with_lock ./p1a $if > $of
done
for if in color/*.input; do
    of=${if/input/output}
    echo "./p1b $if > $of"
    run_with_lock ./p1b $if > $of
done

wait
make clean