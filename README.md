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

Solved N= 100000000  at: 84675 ms Swaps: 205462064 Fails: 1120637037 


Solved N= 10000000  at: 6676 ms Swaps: 20665010 Fails: 116521714 


Solved N= 1000000  at: 673 ms Swaps: 2099038 Fails: 28136002 

Solved N= 100000  at: 47 ms Swaps: 239040 Fails: 4508885 


# Compilation


gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq

or use nqtest.sh which will compile automatically before test.
