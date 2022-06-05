gcc nq.c -Ofast -march=native -mtune=native -Wall -Wno-unused -pipe -onq -DSILENCE $*
time ./nq 40000000

