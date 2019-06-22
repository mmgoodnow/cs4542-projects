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
	outf=${inf/.input/-steep.output}
	run_with_lock ./p5a steep $inf > $outf
done
for inf in knapsack/*.input; do
	outf=${inf/.input/-tabu.output}
	run_with_lock ./p5a tabu $inf > $outf
done
for inf in color/*.input; do
	outf=${inf/.input/-steep.output}
	run_with_lock ./p5b steep $inf > $outf
done
for inf in color/*.input; do
	outf=${inf/.input/-tabu.output}
	run_with_lock ./p5b tabu $inf > $outf
done
wait
make clean
