# NQ.c

Fast N-Queen Puzzle solver

# Syntax

nq N [p|f]

N=Board size 8+

Optional:p=print board as sequence of row addresses from 1+

Optional:f=write board as sequence of uint32's to file N.nq
in working directory.

# Compilation

gcc nq.c -Ofast  -march=native -mtune=native -Wall -onq

