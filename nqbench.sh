gcc nq.c -Ofast -march=native -mtune=native -Wall -Wno-unused -pipe -onq -DSILENCE -DNOFILEINPUT -DNOFILEOUTPUT -DNOSCRAMBLE -DNOPRINTBOARD -DNOINTEGRITY
time ./nq 100000000

