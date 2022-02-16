# NQ.c

Fast N-Queen Puzzle solver

# Syntax

nq N [p|f|t] [filename]

N=Board size 8+

Optional:
p=print board as sequence of row addresses from 1+

f=write board as sequence of uint32's to file N.nq
in working directory.

t=test integrity(nqtest.sh)

i filename=load nqueens file(u32 sequence of row addresses)

# Compilation

(included) C-headers /Util sub-directory

gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq

or use nqtest.sh which will compile automatically before test.
