# NQ.c

Fast N-Queens Puzzle solver using iterative repair

# Syntax

nq N [[num]pftsi] [filename]

N=Board size 8+

Optional:
p=print board as sequence of row addresses from 1+

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

Solved N= 100000000  in 54252 ms(linear solver only)
 Swaps: 208180948 Fails: 123338682 


Solved N= 10000000  in 6042 ms(linear solver only)
 Swaps: 21482393 Fails: 19665379 

 
Solved N= 1000000  in 956 ms(linear solver only)
 Swaps: 2293277 Fails: 5268206 


Solved N= 100000  in 42 ms(linear solver only)
 Swaps: 243299 Fails: 440580 
 

# Compilation


gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq

or use nqtest.sh which will compile automatically before test.
