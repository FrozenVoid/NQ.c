# NQ.c

Fast N-Queen Puzzle solver

# Syntax

nq N [pcftsi] [filename|num]

N=Board size 8+

Optional:
p=print board as sequence of row addresses from 1+

c= additional pedantic O(N^2) checks for diagonals

f=write board as sequence of uint32's to file N.nq
in working directory.

t=generates presolved boards, use to test integrity(nqtest.sh)

i filename=load nqueens file(u32 sequence of row addresses)

num+s  = scramble num times(N*num)

example: nq 1000 12sif file.dat

will load file.dat as N=1000 board,scramble
rows 12 times, solve, then write
the solution to file 1000.nq

# Compilation

(included) C-headers /Util sub-directory

gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq

or use nqtest.sh which will compile automatically before test.
