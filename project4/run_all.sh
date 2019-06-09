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
for inf in knapsack/*.input; do
	outf=${inf/input/output}
	run_with_lock echo "./p2a $inf > $outf"; ./p4 $inf > $outf
done

wait
make clean
