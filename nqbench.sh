gcc nq.c -Ofast -march=native -mtune=native -Wall -Wno-unused -pipe -onq -DSILENCE $*
time ./nq 100000000

