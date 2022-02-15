# NQ.c

Fast N-Queen Puzzle solver

# Syntax

nq N [p|f]

N=Board size 8+

Optional:p=print board as sequence of row addresses from 1+

Optional:f=write board as sequence of uint32's to file N.nq
in working directory.

# Compilation

get C-headers from https://github.com/FrozenVoid/C-headers
place them in /Util sub-directory

gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq

or use nqtest.sh which will compile automatically before test.
