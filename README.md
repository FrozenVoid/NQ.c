# NQ.c

Fast N-Queens Puzzle solver using iterative repair

# Syntax

nq N [[num]pftsi] [filename]

N=Board size 

Optional:
p=print board as sequence of row addresses from 1+

f=write board as sequence of row values to file N.nq
in working directory.

t=generates presolved boards, use to test integrity(nqtest.sh)

i filename=load nqueens file(u32/u64 sequence of row addresses(assumed valid))
(if filename==stdin read string from stdin(e.g. "1 2 3")
(if -DBIGIRON nq.c loads u64 arrays/N upto 2^64-1) 

num+s  = scramble num times(N*num)

example: nq 1000 12sif file.dat

will load file.dat as N=1000 board,scramble
rows 12 times, solve, then write
the solution to file 1000.nq

# Performance

Solved N= 100000000  in  31734 ms(linear solver only)

 

# Compilation


gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq

or use nqtest.sh which will compile automatically before test.
