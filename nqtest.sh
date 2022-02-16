gcc nq.c -Ofast -march=native -mtune=native -Wall -pipe -onq
for (( n=8;n<100000000;n++ ))
do
  echo "Test N-Queens= $n  "
   ./nq $n c
done
