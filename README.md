# NQ.c

Fast N-Queens Puzzle solver using iterative repair

# Syntax

nq N [[num]pcftsi] [filename]

N=Board size 8+

Optional:
p=print board as sequence of row addresses from 1+

c= additional pedantic O(N^2) checks for diagonals

f=write board as sequence of uint32's to file N.nq
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

Solved N= 100000000  at: 417708 ms Swaps: 167401101 Fails: 679418578 

Solved N= 10000000  at: 24719 ms Swaps: 16734583 Fails: 67911304

Solved N= 1000000  at: 2028 ms Swaps: 1675992 Fails: 6861174 

Solved N= 100000  at: 81 ms Swaps: 167017 Fails: 693032

# Compilation

(included) C-headers /Util sub-directory

gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq

or use nqtest.sh which will compile automatically before test.
