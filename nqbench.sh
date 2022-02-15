gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq
time ./nq 10000000
