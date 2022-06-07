# NQ.c

Fast N-Queens Puzzle solver using iterative repair

# Syntax

nq N [[num]pcftsi] [filename]

N=Board size 8+

Optional:
p=print board as sequence of row addresses from 1+

c= additional pedantic checks for diagonals and duplicates

f=write board as sequence of row values to file N.nq
in working directory.

t=generates presolved boards, use to test integrity(nqtest.sh)

i filename=load nqueens file(u32/u64 sequence of row addresses(assumed valid))
if -DBIGIRON nq.c uses u64 arrays/N upto 2^64-1 

num+s  = scramble num times(N*num)

example: nq 1000 12sif file.dat

will load file.dat as N=1000 board,scramble
rows 12 times, solve, then write
the solution to file 1000.nq

# Performance

Solved N= 100000000  at: 189797 ms Swaps: 272750523 Fails: 3851044525

Solved N= 10000000  at: 15266 ms Swaps: 27226067 Fails: 381683658 

Solved N= 1000000  at: 1182 ms Swaps: 2718841 Fails: 38418096 

Solved N= 100000  at: 51 ms Swaps: 272447 Fails: 4091181 

# Compilation


gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq

or use nqtest.sh which will compile automatically before test.
